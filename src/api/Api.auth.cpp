#include <string>
#include <string_view>
#include <stdexcept>

#include <boost/json.hpp>

#include "api/Api.h"

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

    boost::json::value jsonRes = PostRequest("/login", jsonReq);

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

    PostRequest("/logout");

    member_id = std::string();
    token = std::string();
}
