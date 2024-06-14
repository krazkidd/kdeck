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
ApiResult<TResponse> Api::MakeRequest(std::string_view endpoint, bool doPostMethod)
{
    static boost::json::value nullValueSentinel;

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

        req.setOpt(new cURLpp::Options::Url(std::string{kKalshiApiUrl}.append(endpoint)));
        //req.setOpt(new cURLpp::Options::Port(80));

		headers.push_back("Accept: application/json");

        if (IsLoggedIn())
        {
		    headers.push_back(std::string{"Authorization: Bearer "}.append(login.token));
        }

        if (doPostMethod)
        {
            req.setOpt(new cURLpp::Options::Post(true));

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
                headers.push_back("Content-Type: application/json");

                req.setOpt(new cURLpp::Options::PostFields(boost::json::serialize(json)));
            }
        }

        req.setOpt(new cURLpp::Options::HttpHeader(headers));

        req.setOpt(cURLpp::Options::WriteStream(&res));
        req.perform();

        switch (cURLpp::infos::ResponseCode::get(req))
        {
            case 200:
            case 201:
                // success
                return boost::json::value_to<TResponse>(boost::json::parse(res.str()));

            case 204:
                // success (no response body)
                return TResponse{};

            case 400:
            case 401:
            case 403:
            case 404:
            case 500:
            case 503:
                // error
                return boost::json::value_to<ErrorResponse>(boost::json::parse(res.str()));
        }
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

    throw std::runtime_error("Unknown error.");
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
