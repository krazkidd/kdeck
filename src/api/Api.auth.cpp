#include <memory>
#include <string_view>
#include <stdexcept>

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

        OATPP_LOGD("Api", "Login");

        auto req = LoginRequest::createShared();
        req->email = std::string{email};
        req->password = std::string{password};

        ApiResult<LoginResponse> res = HandleResponse<LoginResponse>(_api->Login(userAgent, basePath, req));

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
        OATPP_LOGD("Api", "Logout");

        ApiResult<VoidResponse> res = HandleResponse<VoidResponse>(_api->Logout(userAgent, basePath, login->token));

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
