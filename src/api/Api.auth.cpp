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

        OATPP_LOGD("Api", "Login");

        ApiResult<LoginResponse> res = HandleResponse<LoginResponse>(_api->Login(basePath, req));

        if (std::holds_alternative<std::shared_ptr<LoginResponse>>(res))
        {
            login = std::get<std::shared_ptr<LoginResponse>>(res);

            OATPP_LOGI("Api", "Token = %s", login->token->c_str());
        }
        else
        {
            throw std::runtime_error(std::get<std::shared_ptr<ErrorResponse>>(res)->error->message->c_str());
        }
    }

    void Api::Logout()
    {
        if (!IsLoggedIn())
        {
            throw std::logic_error("Already logged out.");
        }

        OATPP_LOGD("Api", "Logout");

        ApiResult<VoidResponse> res = HandleResponse<VoidResponse>(_api->Logout(basePath, login->token));

        if (std::holds_alternative<std::shared_ptr<VoidResponse>>(res))
        {
            login = nullptr;
        }
        else
        {
            throw std::runtime_error(std::get<std::shared_ptr<ErrorResponse>>(res)->error->message->c_str());
        }
    }

    // helpers /////////////////////////////////////////////////////////////////////

    bool Api::IsLoggedIn()
    {
        return login != nullptr;
    }
}
