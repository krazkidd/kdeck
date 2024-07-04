#ifndef _API_HPP
#define _API_HPP

#include <map>
#include <string_view>
#include <vector>

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/web/client/ApiClient.hpp"

#include "config.hpp"
#include "api/types.hpp"

namespace kdeck
{
    #include OATPP_CODEGEN_BEGIN(ApiClient)

    class _Api
        : public oatpp::web::client::ApiClient
    {

        API_CLIENT_INIT(_Api)

        // NOTE: API_CALL returns std::shared_ptr<IncomingResponse>.
        //       Source: https://oatpp.io/api/latest/oatpp/web/protocol/http/incoming/Response/

        API_CALL_HEADERS(Login)
        {
            headers.put("Content-Type", "application/json");
            headers.put("Accept", "application/json");
        }
        API_CALL("POST", "trade-api/v2/login", Login, BODY_DTO(Object<LoginRequest>, loginRequest))

        API_CALL_HEADERS(Logout)
        {
            headers.put("Content-Type", "application/json");
            headers.put("Accept", "application/json");
        }
        API_CALL("POST", "trade-api/v2/logout", Logout, AUTHORIZATION(String, authString, "Bearer"))

    };

    #include OATPP_CODEGEN_END(ApiClient)

}

#endif
