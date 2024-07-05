#ifndef API_HPP
#define API_HPP

#include <map>
#include <memory>
#include <string_view>
#include <vector>

#include <boost/json.hpp>

#include "oatpp/parser/json/mapping/ObjectMapper.hpp"

#include "config.hpp"
#include "api/types.hpp"
#include "api/_Api.hpp"

namespace kdeck
{
    template <typename TResponse>
    using OatApiResult = std::variant<std::shared_ptr<TResponse>, std::shared_ptr<ErrorResponse>>;

    template <typename TResponse>
    using ApiResult = std::variant<TResponse, ErrorResponse>;

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
        PortfolioPositionsResponse GetPositions();

        // helpers
        bool IsLoggedIn();

        std::vector<PortfolioPositionsResponse::EventPosition> GetEventPositions();
        std::vector<PortfolioPositionsResponse::MarketPosition> GetMarketPositions(std::string_view eventTicker = "");

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
        PortfolioBalanceResponse balance;
        PortfolioPositionsResponse positions;

        std::map<std::string, PortfolioPositionsResponse::EventPosition> eventsMap;
        std::map<std::string, std::map<std::string, PortfolioPositionsResponse::MarketPosition>> marketsMap;

        // core
        template <typename TResponse>
        OatApiResult<TResponse> HandleResponse(std::shared_ptr<oatpp::web::protocol::http::incoming::Response> response);

        template <typename TResponse>
        ApiResult<TResponse> HandleResponse(int responseCode, const std::stringstream &responseBody);

        template <typename TResponse>
        ApiResult<TResponse> MakeRequest(std::string_view endpoint, bool doPostMethod = false);

        template <typename TResponse>
        ApiResult<TResponse> MakeRequest(std::string_view endpoint, const boost::json::value &json, bool doPostMethod = false);

        template <typename TResponse>
        ApiResult<TResponse> GetRequest(std::string_view endpoint);

        template <typename TResponse, typename TRequest>
        ApiResult<TResponse> GetRequest(std::string_view endpoint, TRequest&& req);

        template <typename TResponse>
        ApiResult<TResponse> PostRequest(std::string_view endpoint);

        template <typename TResponse, typename TRequest>
        ApiResult<TResponse> PostRequest(std::string_view endpoint, TRequest&& req);
    };
}

#include "api/Api.hxx"

#endif
