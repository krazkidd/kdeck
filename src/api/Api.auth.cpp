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

        auto loginRequest = LoginRequest::createShared();
        loginRequest->email = std::string{email};
        loginRequest->password = std::string{password};

        OatApiResult<LoginResponse> res = HandleResponse<LoginResponse>(_api->Login(loginRequest));

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

        //TODO refactor after converting VoidResponse to oatpp DTO

        //OatApiResult<VoidResponse> res = HandleResponse<VoidResponse>(_api->Logout(login->token));
        _api->Logout(login->token);

        // if (std::holds_alternative<std::shared_ptr<VoidResponse>>(res))
        {
            login = nullptr;

            OATPP_LOGD("Api", "Logout");
        }
        // else
        // {
        //     throw std::runtime_error(std::get<std::shared_ptr<ErrorResponse>>(res)->message);
        // }
    }

    // helpers /////////////////////////////////////////////////////////////////////

    bool Api::IsLoggedIn()
    {
        return login != nullptr;
    }
}
