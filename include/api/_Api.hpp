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

        API_CALL_HEADERS(GetExchangeAnnouncements)
        {
            headers.put("Content-Type", "application/json");
            headers.put("Accept", "application/json");
        }
        API_CALL("GET", "trade-api/v2/exchange/announcements", GetExchangeAnnouncements)

        API_CALL_HEADERS(GetExchangeSchedule)
        {
            headers.put("Content-Type", "application/json");
            headers.put("Accept", "application/json");
        }
        API_CALL("GET", "trade-api/v2/exchange/schedule", GetExchangeSchedule)

        API_CALL_HEADERS(GetExchangeStatus)
        {
            headers.put("Content-Type", "application/json");
            headers.put("Accept", "application/json");
        }
        API_CALL("GET", "trade-api/v2/exchange/status", GetExchangeStatus)

        API_CALL_HEADERS(GetBalance)
        {
            headers.put("Content-Type", "application/json");
            headers.put("Accept", "application/json");
        }
        API_CALL("GET", "trade-api/v2/portfolio/balance", GetBalance, AUTHORIZATION(String, authString, "Bearer"))

        API_CALL_HEADERS(GetPositions)
        {
            headers.put("Content-Type", "application/json");
            headers.put("Accept", "application/json");
        }
        API_CALL("GET", "trade-api/v2/portfolio/positions", GetPositions, AUTHORIZATION(String, authString, "Bearer"), BODY_DTO(Object<PortfolioPositionsRequest>, portfolioPositionsRequest))

    };

    #include OATPP_CODEGEN_END(ApiClient)

}

#endif
