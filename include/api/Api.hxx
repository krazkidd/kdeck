#include <sstream>
#include <string>
#include <string_view>
#include <utility>
#include <variant>

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>
#include <curlpp/Infos.hpp>
#include <boost/json.hpp>

#include "api/converters.hpp"
#include "api/types.hpp"

template <typename TResponse>
ApiResult<TResponse> Api::HandleResponse(int responseCode, const std::stringstream &responseBody)
{
    switch (responseCode)
    {
        // success
        case 200:
        case 201:
            return boost::json::value_to<TResponse>(boost::json::parse(responseBody.str()));

        // success (no response body)
        case 204:
            // NOTE: If we try to parse an empty body (not valid JSON),
            //       boost::json::parse() will throw. So we just return
            //       the expected type (should be VoidResponse).

            //return boost::json::value_to<TResponse>(boost::json::parse(responseBody.str()));
            return TResponse{};

        // error
        case 400:
        case 401:
        case 403:
        case 404:
        case 500:
        case 503:
            return boost::json::value_to<ErrorResponse>(boost::json::parse(responseBody.str()));
    }

    throw std::runtime_error("Unknown JSON error.");
}

template <typename TResponse>
ApiResult<TResponse> Api::MakeRequest(std::string_view endpoint, bool doPostMethod)
{
    static const boost::json::value nullValueSentinel;

    return MakeRequest<TResponse>(endpoint, nullValueSentinel, doPostMethod);
}

template <typename TResponse>
ApiResult<TResponse> Api::MakeRequest(std::string_view endpoint, const boost::json::value &json, bool doPostMethod)
{
    try
    {
        cURLpp::Easy req;
        std::stringstream res;
        std::list<std::string> headers;

        // uncomment to print requests and responses
        //req.setOpt(new cURLpp::Options::Verbose(true));

        req.setOpt(new cURLpp::Options::Url(std::string{kKalshiApiUrl}.append(endpoint)));
        //req.setOpt(new cURLpp::Options::Port(80));

		headers.push_back(std::string{"Accept: application/json"});

        if (IsLoggedIn())
        {
		    headers.push_back(std::string{"Authorization: Bearer "}.append(login.token));
        }

        if (doPostMethod)
        {
            req.setOpt(new cURLpp::Options::Post(true));

            // NOTE: We are using the POST method, so we have to be explicit about the content type.
            //       By default, libcurl will use application/x-www-form-urlencoded, but the Kalshi API
            //       expects application/json and will return a 400 Bad Request if it doesn't get it.

            headers.push_back(std::string{"Content-Type: application/json"});

            if (json.is_null())
            {
                // NOTE: Because we are using the POST method, we have to be explicit about what to
                //       post, otherwise libcurl will read from standard input. (Also note that an
                //       empty body would not be valid JSON so we don't provide a content type.)
                //
                //       Source: https://github.com/curl/curl/issues/1625#issuecomment-312456910

                req.setOpt(new cURLpp::Options::PostFields(""));
            }
            else
            {
                req.setOpt(new cURLpp::Options::PostFields(boost::json::serialize(json)));
            }
        }

        req.setOpt(new cURLpp::Options::HttpHeader(headers));

        req.setOpt(cURLpp::Options::WriteStream(&res));
        req.perform();

        return HandleResponse<TResponse>(cURLpp::infos::ResponseCode::get(req), res);
    }
    catch (cURLpp::RuntimeError &e)
    {
        //TODO do we want to deal with CURL errors here? (we probably want to provide a user-friendly messaage)
        throw;
    }
    catch (cURLpp::LogicError &e)
    {
        //TODO do we want to deal with CURL errors here? (we probably want to provide a user-friendly messaage)
        throw;
    }

    throw std::runtime_error("Unknown cURL error.");
}

template <typename TResponse>
ApiResult<TResponse> Api::GetRequest(std::string_view endpoint)
{
    return MakeRequest<TResponse>(endpoint);
}

template <typename TResponse, typename TRequest>
ApiResult<TResponse> Api::GetRequest(std::string_view endpoint, TRequest&& req)
{
    boost::json::value jv;
    boost::json::value_from<TRequest>(std::forward<TRequest>(req), jv);

    return MakeRequest<TResponse>(endpoint, jv);
}

template <typename TResponse>
ApiResult<TResponse> Api::PostRequest(std::string_view endpoint)
{
    return MakeRequest<TResponse>(endpoint, true);
}

template <typename TResponse, typename TRequest>
ApiResult<TResponse> Api::PostRequest(std::string_view endpoint, TRequest&& req)
{
    boost::json::value jv;
    boost::json::value_from<TRequest>(std::forward<TRequest>(req), jv);

    return MakeRequest<TResponse>(endpoint, jv, true);
}
