#include <string_view>
#include <utility>

#include <boost/json.hpp>

boost::json::value Api::MakeRequest(std::string_view endpoint, bool doPostMethod)
{
    static boost::json::value nullValueSentinel;

    return MakeRequest(endpoint, nullValueSentinel, doPostMethod);
}

boost::json::value Api::MakeRequest(std::string_view endpoint, const boost::json::value &json, bool doPostMethod)
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

        if (cURLpp::infos::ResponseCode::get(req) == 200)
        {
            // success

            return boost::json::parse(res.str());
        }
        else if (cURLpp::infos::ResponseCode::get(req) == 204)
        {
            // success (no response body)

            return boost::json::value();
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

}

void Api::GetRequest(std::string_view endpoint)
{
    MakeRequest(endpoint);
}

template <typename TResponse>
TResponse Api::GetRequest(std::string_view endpoint)
{
    return boost::json::value_to<TResponse>(MakeRequest(endpoint));
}

template <typename TResponse, typename TRequest>
TResponse Api::GetRequest(std::string_view endpoint, TRequest&& req)
{
    boost::json::value jv;
    boost::json::value_from<TRequest>(std::forward<TRequest>(req), jv);


void Api::PostRequest(std::string_view endpoint)
{
    MakeRequest(endpoint, true);
}

template <typename TResponse>
TResponse Api::PostRequest(std::string_view endpoint)
{
    return boost::json::value_to<TResponse>(MakeRequest(endpoint, true));
}

template <typename TResponse, typename TRequest>
TResponse Api::PostRequest(std::string_view endpoint, TRequest&& req)
{
    boost::json::value jv;
    boost::json::value_from<TRequest>(std::forward<TRequest>(req), jv);

    return boost::json::value_to<TResponse>(MakeRequest(endpoint, jv, true));
}
