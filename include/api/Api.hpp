#ifndef API_HPP
#define API_HPP

#include <map>
#include <memory>
#include <string_view>
#include <list>
#include <variant>

#include "oatpp/parser/json/mapping/ObjectMapper.hpp"

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

        // market
        std::shared_ptr<EventsResponse> GetEvents();
        std::shared_ptr<EventResponse> GetEvent(std::string_view eventTicker);
        std::shared_ptr<MarketsResponse> GetMarkets();
        std::shared_ptr<TradesResponse> GetTrades();
        std::shared_ptr<MarketResponse> GetMarket(std::string_view marketTicker);
        std::shared_ptr<MarketOrderbookResponse> GetMarketOrderbook(std::string_view marketTicker);
        std::shared_ptr<SeriesResponse> GetSeries(std::string_view seriesTicker);
        std::shared_ptr<MarketCandlesticksResponse> GetMarketCandlesticks(std::string_view seriesTicker, std::string_view marketTicker);

        // portfolio
        double GetBalance();
        std::shared_ptr<FillsResponse> GetFills();
        std::shared_ptr<OrdersResponse> GetOrders();
        std::shared_ptr<OrderResponse> CreateOrder();
        std::shared_ptr<OrderResponse> GetOrder(std::string_view orderId);
        std::shared_ptr<CancelOrderResponse> CancelOrder(std::string_view orderId);
        std::shared_ptr<AmendOrderResponse> AmendOrder(std::string_view orderId);
        std::shared_ptr<OrderResponse> DecreaseOrder(std::string_view orderId);
        std::shared_ptr<PortfolioPositionsResponse> GetPositions();
        std::shared_ptr<PortfolioSettlementsResponse> GetPortfolioSettlements();

        // helpers
        bool IsLoggedIn();

        std::list<std::shared_ptr<EventPosition>> GetEventPositions();
        std::list<std::shared_ptr<MarketPosition>> GetMarketPositions(std::string_view eventTicker = "");

    private:
        std::string basePath;
        std::shared_ptr<oatpp::parser::json::mapping::ObjectMapper> objectMapper;
        std::shared_ptr<_Api> _api;

        // auth
        std::shared_ptr<LoginResponse> login;

        // exchange
        std::shared_ptr<ExchangeAnnouncementsResponse> announcements;
        std::shared_ptr<ExchangeScheduleResponse> schedule;
        std::shared_ptr<ExchangeStatusResponse> status;

        // market
        std::shared_ptr<EventsResponse> events;
        std::shared_ptr<MarketsResponse> markets;

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
