#ifndef API_HPP
#define API_HPP

#include <map>
#include <memory>
#include <string_view>
#include <list>
#include <variant>

#include "oatpp/parser/json/mapping/ObjectMapper.hpp"

#include "config.hpp"
#include "api/types.hpp"
#include "api/_Api.hpp"

namespace kdeck
{
    template <typename TResponse>
    using ApiResult = std::variant<std::shared_ptr<TResponse>, std::shared_ptr<ErrorResponse>>;

    class Api
    {
    public:
        Api(std::string_view apiEndpointUrl, std::string_view sslTrustStoreDir = {});

        // auth
        void Login(std::string_view email, std::string_view password);
        void Logout();

        // exchange
        std::shared_ptr<ExchangeAnnouncementsResponse> GetExchangeAnnouncements();
        std::shared_ptr<ExchangeScheduleResponse> GetExchangeSchedule();
        std::shared_ptr<ExchangeStatusResponse> GetExchangeStatus();

        // portfolio
        double GetBalance();
        std::shared_ptr<PortfolioPositionsResponse> GetPositions();

        // helpers
        bool IsLoggedIn();

        std::list<std::shared_ptr<EventPosition>> GetEventPositions();
        std::list<std::shared_ptr<MarketPosition>> GetMarketPositions(std::string_view eventTicker = "");

    private:
        std::shared_ptr<oatpp::parser::json::mapping::ObjectMapper> objectMapper;
        std::shared_ptr<_Api> _api;

        // auth
        std::shared_ptr<LoginResponse> login;

        // exchange
        std::shared_ptr<ExchangeAnnouncementsResponse> announcements;
        std::shared_ptr<ExchangeScheduleResponse> schedule;
        std::shared_ptr<ExchangeStatusResponse> status;

        // portfolio
        std::shared_ptr<PortfolioBalanceResponse> balance;
        std::shared_ptr<PortfolioPositionsResponse> positions;

        std::map<std::string, std::shared_ptr<EventPosition>> eventsMap;
        std::map<std::string, std::map<std::string, std::shared_ptr<MarketPosition>>> marketsMap;

        // core
        template <typename TResponse>
        ApiResult<TResponse> HandleResponse(std::shared_ptr<oatpp::web::protocol::http::incoming::Response> response);

    };
}

#include "api/Api.hxx"

#endif
