#include <sstream>
#include <string>
#include <string_view>
#include <stdexcept>

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>
#include <curlpp/Infos.hpp>
#include <boost/json.hpp>

#include "config.h"
#include "Api.h"

boost::json::value Api::MakeRequest(std::string_view endpoint)
{
    static boost::json::value nullValueSentinel;

    return MakeRequest(endpoint, nullValueSentinel);
}

boost::json::value Api::MakeRequest(std::string_view endpoint, const boost::json::value &json)
{
    try
    {
        cURLpp::Easy req;
        std::stringstream res;

        req.setOpt(new cURLpp::Options::Post(true));
        req.setOpt(new cURLpp::Options::Url(std::string{kKalshiApiUrl}.append(endpoint)));
        //req.setOpt(new cURLpp::Options::Port(80));

        std::list<std::string> headers;
		headers.push_back("Accept: application/json");

        if (IsLoggedIn())
        {
		    headers.push_back(std::string{"Authorization: Bearer "}.append(token));
        }

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

    //TODO do we want to throw an exception here? (note that /logout returns 204, not 200)
    return boost::json::value();
}

// auth ///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void Api::Login(std::string_view email, std::string_view password)
{
    if (IsLoggedIn())
    {
        throw std::logic_error("Already logged in.");
    }
    else if (email.empty())
    {
        throw std::invalid_argument("Email not provided.");
    }
    else if (password.empty())
    {
        throw std::invalid_argument("Password not provided.");
    }

    boost::json::object jsonReq = {
        { "email", email },
        { "password", password }
    };

    boost::json::value jsonRes = MakeRequest("/login", jsonReq);

    if (auto jsonObj = jsonRes.if_object())
    {
        member_id = jsonObj->at("member_id").as_string();
        token = jsonObj->at("token").as_string();
    }
    else
    {
        //TODO throw?
    }
}

void Api::Logout()
{
    if (!IsLoggedIn())
    {
        throw std::logic_error("Already logged out.");
    }

    MakeRequest("/logout");

    member_id = std::string();
    token = std::string();
}

// helpers ////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

bool Api::IsLoggedIn()
{
    return !member_id.empty();
}
