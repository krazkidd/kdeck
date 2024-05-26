#include <sstream>
#include <string>
#include <stdexcept>

#include <fmt/core.h>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>
#include <curlpp/Infos.hpp>

#include "config.h"
#include "Api.h"

std::string Api::MakeRequest(std::string endpoint, std::string json)
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
            return res.str();
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
    return std::string();
}

// API requests ///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

std::string Api::RequestLoginToken(std::string email, std::string password)
{
    if (email.empty())
    {
        throw std::invalid_argument("Email not provided.");
    }
    else if (password.empty())
    {
        throw std::invalid_argument("Password not provided.");
    }

    return Api::MakeRequest(std::string{"/login"}, fmt::format(
        "{{"
            "\"email\":\"{0}\","
            "\"password\":\"{1}\""
        "}}"
    , email, password));
}
