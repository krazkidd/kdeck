#include <memory>
#include <string_view>
#include <stdexcept>
#include <variant>

#include "oatpp/core/base/Environment.hpp"

#include "api/Api.hpp"
#include "api/types.hpp"

namespace kdeck
{
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

        auto req = LoginRequest::createShared();
        req->email = std::string{email};
        req->password = std::string{password};

        ApiResult<LoginResponse> res = HandleResponse<LoginResponse>(_api->Login(basePath, req));

        if (std::holds_alternative<std::shared_ptr<LoginResponse>>(res))
        {
            login = std::get<std::shared_ptr<LoginResponse>>(res);

            OATPP_LOGD("Api", "Login (auth token = %s)", login->token->c_str());
        }
        else
        {
            throw std::runtime_error(std::get<std::shared_ptr<ErrorResponse>>(res)->message);
        }
    }

    void Api::Logout()
    {
        if (!IsLoggedIn())
        {
            throw std::logic_error("Already logged out.");
        }

        ApiResult<VoidResponse> res = HandleResponse<VoidResponse>(_api->Logout(basePath, login->token));

        if (std::holds_alternative<std::shared_ptr<VoidResponse>>(res))
        {
            login = nullptr;

            OATPP_LOGD("Api", "Logout");
        }
        else
        {
            throw std::runtime_error(std::get<std::shared_ptr<ErrorResponse>>(res)->message);
        }
    }

    // helpers /////////////////////////////////////////////////////////////////////

    bool Api::IsLoggedIn()
    {
        return login != nullptr;
    }
}
