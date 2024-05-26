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
        headers.push_back("Content-Type: application/json");
        req.setOpt(new cURLpp::Options::HttpHeader(headers));

        req.setOpt(new cURLpp::Options::PostFields(json));

        req.setOpt(cURLpp::Options::WriteStream(&res));
        req.perform();

        if (cURLpp::infos::ResponseCode::get(req) == 200)
        {
            return boost::json::parse(res.str());
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
    if (email.empty())
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
}
