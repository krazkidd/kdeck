#ifndef _API_HPP
#define _API_HPP

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/web/client/ApiClient.hpp"

namespace kdeck
{
    #include OATPP_CODEGEN_BEGIN(ApiClient)

    class _Api
        : public oatpp::web::client::ApiClient
    {

        // NOTE: API_CALL returns std::shared_ptr<IncomingResponse>.
        //       Source: https://oatpp.io/api/latest/oatpp/web/protocol/http/incoming/Response/

        API_CLIENT_INIT(_Api)

        // auth /////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////////////

        API_CALL_HEADERS(Login)
        {
            headers.put("Content-Type", "application/json");
            headers.put("Accept", "application/json");
        }
        API_CALL("POST", "{basePath}/login", Login, PATH(String, basePath), BODY_DTO(Object<LoginRequest>, loginRequest))

        API_CALL_HEADERS(Logout)
        {
            headers.put("Content-Type", "application/json");
            headers.put("Accept", "application/json");
        }
        API_CALL("POST", "{basePath}/logout", Logout, PATH(String, basePath), AUTHORIZATION(String, authString, "Bearer"))

        // exchange /////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////////////

        API_CALL_HEADERS(GetExchangeAnnouncements)
        {
            headers.put("Accept", "application/json");
        }
        API_CALL("GET", "{basePath}/exchange/announcements", GetExchangeAnnouncements, PATH(String, basePath))

        API_CALL_HEADERS(GetExchangeSchedule)
        {
            headers.put("Accept", "application/json");
        }
        API_CALL("GET", "{basePath}/exchange/schedule", GetExchangeSchedule, PATH(String, basePath))

        API_CALL_HEADERS(GetExchangeStatus)
        {
            headers.put("Accept", "application/json");
        }
        API_CALL("GET", "{basePath}/exchange/status", GetExchangeStatus, PATH(String, basePath))

        // market ///////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////////////

        API_CALL_HEADERS(GetEvents)
        {
            headers.put("Content-Type", "application/json");
            headers.put("Accept", "application/json");
        }
        API_CALL("GET", "{basePath}/events", GetEvents, PATH(String, basePath), BODY_DTO(Object<EventsRequest>, eventsRequest))

        API_CALL_HEADERS(GetEvent)
        {
            headers.put("Content-Type", "application/json");
            headers.put("Accept", "application/json");
        }
        API_CALL("GET", "{basePath}/events/{event_ticker}", GetEvent, PATH(String, basePath), PATH(String, event_ticker), BODY_DTO(Object<EventRequest>, eventRequest))

        API_CALL_HEADERS(GetMarkets)
        {
            headers.put("Content-Type", "application/json");
            headers.put("Accept", "application/json");
        }
        API_CALL("GET", "{basePath}/markets", GetMarkets, PATH(String, basePath), AUTHORIZATION(String, authString, "Bearer"), BODY_DTO(Object<MarketsRequest>, marketsRequest))

        API_CALL_HEADERS(GetTrades)
        {
            headers.put("Content-Type", "application/json");
            headers.put("Accept", "application/json");
        }
        API_CALL("GET", "{basePath}/markets/trades", GetTrades, PATH(String, basePath), BODY_DTO(Object<TradesRequest>, tradesRequest))

        API_CALL_HEADERS(GetMarket)
        {
            headers.put("Accept", "application/json");
        }
        API_CALL("GET", "{basePath}/markets/{ticker}", GetMarket, PATH(String, basePath), PATH(String, ticker))

        API_CALL_HEADERS(GetMarketOrderbook)
        {
            headers.put("Content-Type", "application/json");
            headers.put("Accept", "application/json");
        }
        API_CALL("GET", "{basePath}/markets/{ticker}/orderbook", GetMarketOrderbook, PATH(String, basePath), AUTHORIZATION(String, authString, "Bearer"), QUERY(String, ticker), BODY_DTO(Object<MarketOrderbookRequest>, marketOrderbookRequest))

        API_CALL_HEADERS(GetSeries)
        {
            headers.put("Accept", "application/json");
        }
        API_CALL("GET", "{basePath}/series/{series_ticker}", GetSeries, PATH(String, basePath), PATH(String, series_ticker))

        API_CALL_HEADERS(GetMarketCandlesticks)
        {
            headers.put("Content-Type", "application/json");
            headers.put("Accept", "application/json");
        }
        API_CALL("GET", "{basePath}/series/{series_ticker}/markets/{ticker}/candlesticks", GetMarketCandlesticks, PATH(String, basePath), AUTHORIZATION(String, authString, "Bearer"), PATH(String, series_ticker), PATH(String, ticker), BODY_DTO(Object<MarketCandlesticksRequest>, marketCandlesticksRequest))

        // portfolio ////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////////////

        API_CALL_HEADERS(GetBalance)
        {
            headers.put("Accept", "application/json");
        }
        API_CALL("GET", "{basePath}/portfolio/balance", GetBalance, PATH(String, basePath), AUTHORIZATION(String, authString, "Bearer"))

        API_CALL_HEADERS(GetFills)
        {
            headers.put("Content-Type", "application/json");
            headers.put("Accept", "application/json");
        }
        API_CALL("GET", "{basePath}/portfolio/fills", GetFills, PATH(String, basePath), AUTHORIZATION(String, authString, "Bearer"), BODY_DTO(Object<FillsRequest>, req))

        API_CALL_HEADERS(GetOrders)
        {
            headers.put("Content-Type", "application/json");
            headers.put("Accept", "application/json");
        }
        API_CALL("GET", "{basePath}/portfolio/orders", GetOrders, PATH(String, basePath), AUTHORIZATION(String, authString, "Bearer"), BODY_DTO(Object<OrdersRequest>, req))

        API_CALL_HEADERS(CreateOrder)
        {
            headers.put("Content-Type", "application/json");
            headers.put("Accept", "application/json");
        }
        API_CALL("POST", "{basePath}/portfolio/orders", CreateOrder, PATH(String, basePath), AUTHORIZATION(String, authString, "Bearer"), BODY_DTO(Object<CreateOrderRequest>, req))

        API_CALL_HEADERS(GetOrder)
        {
            headers.put("Content-Type", "application/json");
            headers.put("Accept", "application/json");
        }
        API_CALL("GET", "{basePath}/portfolio/orders/{order_id}", GetOrder, PATH(String, basePath), AUTHORIZATION(String, authString, "Bearer"), PATH(String, order_id))

        API_CALL_HEADERS(CancelOrder)
        {
            headers.put("Content-Type", "application/json");
            headers.put("Accept", "application/json");
        }
        API_CALL("DELETE", "{basePath}/portfolio/orders/{order_id}", CancelOrder, PATH(String, basePath), AUTHORIZATION(String, authString, "Bearer"), PATH(String, order_id))

        API_CALL_HEADERS(AmendOrder)
        {
            headers.put("Content-Type", "application/json");
            headers.put("Accept", "application/json");
        }
        API_CALL("POST", "{basePath}/portfolio/orders/{order_id}/amend", AmendOrder, PATH(String, basePath), AUTHORIZATION(String, authString, "Bearer"), PATH(String, order_id), BODY_DTO(Object<AmendOrderRequest>, req))

        API_CALL_HEADERS(DecreaseOrder)
        {
            headers.put("Content-Type", "application/json");
            headers.put("Accept", "application/json");
        }
        API_CALL("POST", "{basePath}/portfolio/orders/{order_id}/decrease", DecreaseOrder, PATH(String, basePath), AUTHORIZATION(String, authString, "Bearer"), PATH(String, order_id), BODY_DTO(Object<DecreaseOrderRequest>, req))

        API_CALL_HEADERS(GetPositions)
        {
            headers.put("Content-Type", "application/json");
            headers.put("Accept", "application/json");
        }
        API_CALL("GET", "{basePath}/portfolio/positions", GetPositions, PATH(String, basePath), AUTHORIZATION(String, authString, "Bearer"), BODY_DTO(Object<PortfolioPositionsRequest>, portfolioPositionsRequest))

        API_CALL_HEADERS(GetPortfolioSettlements)
        {
            headers.put("Content-Type", "application/json");
            headers.put("Accept", "application/json");
        }
        API_CALL("GET", "{basePath}/portfolio/settlements", GetPortfolioSettlements, PATH(String, basePath), AUTHORIZATION(String, authString, "Bearer"), BODY_DTO(Object<PortfolioSettlementsRequest>, req))

    };

    #include OATPP_CODEGEN_END(ApiClient)

}

#endif
