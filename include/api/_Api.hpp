#ifndef _API_HPP
#define _API_HPP

#include "oatpp/core/Types.hpp"
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
        API_CALL("POST", "{basePath}/login", Login, HEADER(String, userAgent, "User-Agent"), PATH(String, basePath), BODY_DTO(Object<LoginRequest>, req))

        API_CALL_HEADERS(Logout)
        {
            headers.put("Content-Type", "application/json");
            headers.put("Accept", "application/json");
        }
        API_CALL("POST", "{basePath}/logout", Logout, HEADER(String, userAgent, "User-Agent"), PATH(String, basePath), AUTHORIZATION(String, authString, "Bearer"))

        // exchange /////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////////////

        API_CALL_HEADERS(GetExchangeAnnouncements)
        {
            headers.put("Accept", "application/json");
        }
        API_CALL("GET", "{basePath}/exchange/announcements", GetExchangeAnnouncements, HEADER(String, userAgent, "User-Agent"), PATH(String, basePath))

        API_CALL_HEADERS(GetExchangeSchedule)
        {
            headers.put("Accept", "application/json");
        }
        API_CALL("GET", "{basePath}/exchange/schedule", GetExchangeSchedule, HEADER(String, userAgent, "User-Agent"), PATH(String, basePath))

        API_CALL_HEADERS(GetExchangeStatus)
        {
            headers.put("Accept", "application/json");
        }
        API_CALL("GET", "{basePath}/exchange/status", GetExchangeStatus, HEADER(String, userAgent, "User-Agent"), PATH(String, basePath))

        // market ///////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////////////

        API_CALL_HEADERS(GetEvents)
        {
            headers.put("Content-Type", "application/json");
            headers.put("Accept", "application/json");
        }
        API_CALL(
            "GET",
            "{basePath}/events",
            GetEvents,
            HEADER(String, userAgent, "User-Agent"),
            PATH(String, basePath),
            QUERY(String, cursor),
            QUERY(Int32, limit),
            QUERY(String, status),
            QUERY(String, series_ticker),
            QUERY(Boolean, with_nested_markets)
        )

        API_CALL_HEADERS(GetEvent)
        {
            headers.put("Content-Type", "application/json");
            headers.put("Accept", "application/json");
        }
        API_CALL(
            "GET",
            "{basePath}/events/{event_ticker}",
            GetEvent,
            HEADER(String, userAgent, "User-Agent"),
            PATH(String, basePath),
            PATH(String, event_ticker),
            QUERY(Boolean, with_nested_markets)
        )

        API_CALL_HEADERS(GetMarkets)
        {
            headers.put("Content-Type", "application/json");
            headers.put("Accept", "application/json");
        }
        API_CALL(
            "GET",
            "{basePath}/markets",
            GetMarkets,
            HEADER(String, userAgent, "User-Agent"),
            PATH(String, basePath),
            AUTHORIZATION(String, authString, "Bearer"),
            QUERY(String, cursor),
            QUERY(Int32, limit),
            QUERY(String, event_ticker),
            QUERY(String, series_ticker),
            QUERY(Int64, max_close_ts),
            QUERY(Int64, min_close_ts),
            QUERY(String, status),
            QUERY(String, tickers)
        )

        API_CALL_HEADERS(GetTrades)
        {
            headers.put("Content-Type", "application/json");
            headers.put("Accept", "application/json");
        }
        API_CALL(
            "GET",
            "{basePath}/markets/trades",
            GetTrades,
            HEADER(String, userAgent, "User-Agent"),
            PATH(String, basePath),
            QUERY(String, cursor),
            QUERY(Int32, limit),
            QUERY(String, ticker),
            QUERY(Int64, min_ts),
            QUERY(Int64, max_ts)
        )

        API_CALL_HEADERS(GetMarket)
        {
            headers.put("Accept", "application/json");
        }
        API_CALL("GET", "{basePath}/markets/{ticker}", GetMarket, HEADER(String, userAgent, "User-Agent"), PATH(String, basePath), PATH(String, ticker))

        API_CALL_HEADERS(GetMarketOrderbook)
        {
            headers.put("Content-Type", "application/json");
            headers.put("Accept", "application/json");
        }
        API_CALL(
            "GET",
            "{basePath}/markets/{ticker}/orderbook",
            GetMarketOrderbook,
            HEADER(String, userAgent, "User-Agent"),
            PATH(String, basePath),
            AUTHORIZATION(String, authString, "Bearer"),
            QUERY(String, ticker),
            QUERY(Int32, depth)
        )

        API_CALL_HEADERS(GetSeries)
        {
            headers.put("Accept", "application/json");
        }
        API_CALL("GET", "{basePath}/series/{series_ticker}", GetSeries, HEADER(String, userAgent, "User-Agent"), PATH(String, basePath), PATH(String, series_ticker))

        API_CALL_HEADERS(GetMarketCandlesticks)
        {
            headers.put("Content-Type", "application/json");
            headers.put("Accept", "application/json");
        }
        API_CALL(
            "GET",
            "{basePath}/series/{series_ticker}/markets/{ticker}/candlesticks",
            GetMarketCandlesticks,
            HEADER(String, userAgent, "User-Agent"),
            PATH(String, basePath),
            AUTHORIZATION(String, authString, "Bearer"),
            PATH(String, series_ticker), PATH(String, ticker),
            QUERY(Int64, start_ts),
            QUERY(Int64, end_ts),
            QUERY(Int64, period_interval)
        )

        // portfolio ////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////////////

        API_CALL_HEADERS(GetBalance)
        {
            headers.put("Accept", "application/json");
        }
        API_CALL("GET", "{basePath}/portfolio/balance", GetBalance, HEADER(String, userAgent, "User-Agent"), PATH(String, basePath), AUTHORIZATION(String, authString, "Bearer"))

        API_CALL_HEADERS(GetFills)
        {
            headers.put("Content-Type", "application/json");
            headers.put("Accept", "application/json");
        }
        API_CALL(
            "GET",
            "{basePath}/portfolio/fills",
            GetFills,
            HEADER(String, userAgent, "User-Agent"),
            PATH(String, basePath),
            AUTHORIZATION(String, authString, "Bearer"),
            QUERY(String, ticker),
            QUERY(String, order_id),
            QUERY(Int64, min_ts),
            QUERY(Int64, max_ts),
            QUERY(Int32, limit),
            QUERY(String, cursor)
        )

        API_CALL_HEADERS(GetOrders)
        {
            headers.put("Content-Type", "application/json");
            headers.put("Accept", "application/json");
        }
        API_CALL(
            "GET",
            "{basePath}/portfolio/orders",
            GetOrders,
            HEADER(String, userAgent, "User-Agent"),
            PATH(String, basePath),
            AUTHORIZATION(String, authString, "Bearer"),
            QUERY(String, ticker),
            QUERY(String, event_ticker),
            QUERY(Int64, min_ts),
            QUERY(Int64, max_ts),
            QUERY(String, status),
            QUERY(String, cursor),
            QUERY(Int32, limit)
        )

        API_CALL_HEADERS(CreateOrder)
        {
            headers.put("Content-Type", "application/json");
            headers.put("Accept", "application/json");
        }
        API_CALL("POST", "{basePath}/portfolio/orders", CreateOrder, HEADER(String, userAgent, "User-Agent"), PATH(String, basePath), AUTHORIZATION(String, authString, "Bearer"), BODY_DTO(Object<CreateOrderRequest>, req))

        API_CALL_HEADERS(GetOrder)
        {
            headers.put("Content-Type", "application/json");
            headers.put("Accept", "application/json");
        }
        API_CALL("GET", "{basePath}/portfolio/orders/{order_id}", GetOrder, HEADER(String, userAgent, "User-Agent"), PATH(String, basePath), AUTHORIZATION(String, authString, "Bearer"), PATH(String, order_id))

        API_CALL_HEADERS(CancelOrder)
        {
            headers.put("Content-Type", "application/json");
            headers.put("Accept", "application/json");
        }
        API_CALL("DELETE", "{basePath}/portfolio/orders/{order_id}", CancelOrder, HEADER(String, userAgent, "User-Agent"), PATH(String, basePath), AUTHORIZATION(String, authString, "Bearer"), PATH(String, order_id))

        API_CALL_HEADERS(AmendOrder)
        {
            headers.put("Content-Type", "application/json");
            headers.put("Accept", "application/json");
        }
        API_CALL("POST", "{basePath}/portfolio/orders/{order_id}/amend", AmendOrder, HEADER(String, userAgent, "User-Agent"), PATH(String, basePath), AUTHORIZATION(String, authString, "Bearer"), PATH(String, order_id), BODY_DTO(Object<AmendOrderRequest>, req))

        API_CALL_HEADERS(DecreaseOrder)
        {
            headers.put("Content-Type", "application/json");
            headers.put("Accept", "application/json");
        }
        API_CALL("POST", "{basePath}/portfolio/orders/{order_id}/decrease", DecreaseOrder, HEADER(String, userAgent, "User-Agent"), PATH(String, basePath), AUTHORIZATION(String, authString, "Bearer"), PATH(String, order_id), BODY_DTO(Object<DecreaseOrderRequest>, req))

        API_CALL_HEADERS(GetPositions)
        {
            headers.put("Content-Type", "application/json");
            headers.put("Accept", "application/json");
        }
        API_CALL(
            "GET",
            "{basePath}/portfolio/positions",
            GetPositions,
            HEADER(String, userAgent, "User-Agent"),
            PATH(String, basePath),
            AUTHORIZATION(String, authString, "Bearer"),
            QUERY(String, cursor),
            QUERY(Int32, limit),
            QUERY(String, count_filter),
            QUERY(String, settlement_status),
            QUERY(String, ticker),
            QUERY(String, event_ticker)
        )

        API_CALL_HEADERS(GetPortfolioSettlements)
        {
            headers.put("Content-Type", "application/json");
            headers.put("Accept", "application/json");
        }
        API_CALL(
            "GET",
            "{basePath}/portfolio/settlements",
            GetPortfolioSettlements,
            HEADER(String, userAgent, "User-Agent"),
            PATH(String, basePath),
            AUTHORIZATION(String, authString, "Bearer"),
            QUERY(Int64, limit),
            QUERY(String, cursor)
        )

    };

    #include OATPP_CODEGEN_END(ApiClient)

}

#endif
