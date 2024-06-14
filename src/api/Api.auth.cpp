#include <string_view>
#include <stdexcept>
#include <variant>

#include "api/Api.hpp"
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

    ApiResult<LoginResponse> res = PostRequest<LoginResponse, LoginRequest>("/login", LoginRequest{email, password});

    if (std::holds_alternative<LoginResponse>(res))
    {
        login = std::get<LoginResponse>(res);
    }
    else
    {
        throw std::runtime_error(std::get<ErrorResponse>(res).message);
    }
}

void Api::Logout()
{
    if (!IsLoggedIn())
    {
        throw std::logic_error("Already logged out.");
    }

    ApiResult<VoidResponse> res = PostRequest<VoidResponse>("/logout");

    if (std::holds_alternative<VoidResponse>(res))
    {
        login = LoginResponse{};
    }
    else
    {
        throw std::runtime_error(std::get<ErrorResponse>(res).message);
    }
}

// helpers /////////////////////////////////////////////////////////////////////

bool Api::IsLoggedIn()
{
    return !login.member_id.empty();
}
