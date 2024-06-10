#include <string>
#include <string_view>
#include <stdexcept>

#include <boost/json.hpp>

#include "api/Api.hpp"
#include "api/converters.hpp"
#include "api/types.hpp"

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

    login = PostRequest<LoginResponse, LoginRequest>("/login", LoginRequest{email, password});
}

void Api::Logout()
{
    if (!IsLoggedIn())
    {
        throw std::logic_error("Already logged out.");
    }

    PostRequest("/logout");

    login = LoginResponse{};
}
