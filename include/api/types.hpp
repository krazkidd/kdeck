#ifndef TYPES_HPP
#define TYPES_HPP

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

namespace kdeck
{

    // Kalshi defines "date-time" type as a string in the ISO8601 format (e.g. "2024-07-07T20:17:11.558Z")
    typedef oatpp::String DateTime_Iso8601;
    // for simple daily hours, Kalshi returns a string in the format "HH:MM" (24-hour clock in their local time zone, Eastern Time)
    typedef oatpp::String EasternTime_HH_MM;

    #include OATPP_CODEGEN_BEGIN(DTO)

    class VoidResponse
        : public oatpp::DTO
    {

        DTO_INIT(VoidResponse, DTO /* extends */)

    };

    class Error
        : public oatpp::DTO
    {

        DTO_INIT(Error, DTO /* extends */)

        DTO_FIELD(String, code);
        DTO_FIELD(String, message);
        DTO_FIELD(String, service);

    };

    class ErrorResponse
        : public oatpp::DTO
    {

        DTO_INIT(ErrorResponse, DTO /* extends */)

        DTO_FIELD(Object<Error>, error);

    };

    // auth /////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////

    class LoginRequest
        : public oatpp::DTO
    {

        DTO_INIT(LoginRequest, DTO /* extends */)

        DTO_FIELD(String, email);
        DTO_FIELD(String, password);

    };

    class LoginResponse
        : public oatpp::DTO
    {

        DTO_INIT(LoginResponse, DTO /* extends */)

        DTO_FIELD(String, member_id);
        DTO_FIELD(String, token);

    };

    // exchange /////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////

    class Announcement
        : public oatpp::DTO
    {

        DTO_INIT(Announcement, DTO /* extends */)

        DTO_FIELD(DateTime_Iso8601, delivery_time);
        DTO_FIELD(String, message);
        DTO_FIELD(String, status);
        DTO_FIELD(String, type);

    };

    class MaintenanceWindow
        : public oatpp::DTO
    {

        DTO_INIT(MaintenanceWindow, DTO /* extends */)

        DTO_FIELD(DateTime_Iso8601, start_datetime);
        DTO_FIELD(DateTime_Iso8601, end_datetime);

    };

    class DailyHours
        : public oatpp::DTO
    {

        DTO_INIT(DailyHours, DTO /* extends */)

        DTO_FIELD(EasternTime_HH_MM, open_time);
        DTO_FIELD(EasternTime_HH_MM, close_time);

    };

    class StandardHours
        : public oatpp::DTO
    {

        DTO_INIT(StandardHours, DTO /* extends */)

        DTO_FIELD(Object<DailyHours>, sunday);
        DTO_FIELD(Object<DailyHours>, monday);
        DTO_FIELD(Object<DailyHours>, tuesday);
        DTO_FIELD(Object<DailyHours>, wednesday);
        DTO_FIELD(Object<DailyHours>, thursday);
        DTO_FIELD(Object<DailyHours>, friday);
        DTO_FIELD(Object<DailyHours>, saturday);

    };

    class Schedule
        : public oatpp::DTO
    {

        DTO_INIT(Schedule, DTO /* extends */)

        DTO_FIELD(List<Object<MaintenanceWindow>>, maintenance_windows);
        DTO_FIELD(Object<StandardHours>, standard_hours);

    };

    class ExchangeAnnouncementsResponse
        : public oatpp::DTO
    {

        DTO_INIT(ExchangeAnnouncementsResponse, DTO /* extends */)

        DTO_FIELD(List<Object<Announcement>>, announcements);

    };

    struct ExchangeScheduleResponse
        : public oatpp::DTO
    {

        DTO_INIT(ExchangeScheduleResponse, DTO /* extends */)

        DTO_FIELD(Object<Schedule>, schedule);

    };

    struct ExchangeStatusResponse
        : public oatpp::DTO
    {

        DTO_INIT(ExchangeStatusResponse, DTO /* extends */)

        DTO_FIELD(Boolean, exchange_active);
        DTO_FIELD(Boolean, trading_active);

    };

    // markets //////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////

    struct EventsRequest
        : public oatpp::DTO
    {

        DTO_INIT(EventsRequest, DTO /* extends */)

        DTO_FIELD(String, cursor);
        DTO_FIELD(Int32, limit);
        DTO_FIELD(String, status);
        DTO_FIELD(String, series_ticker);
        DTO_FIELD(Boolean, with_nested_markets);

    };

    struct Market
        : public oatpp::DTO
    {

        DTO_INIT(Market, DTO /* extends */)

        DTO_FIELD(Boolean, can_close_early);
        DTO_FIELD(Float64, cap_strike);
        DTO_FIELD(String, category);
        DTO_FIELD(DateTime_Iso8601, close_time);
        //TODO filled only if "strike_type" is "custom"
        //DTO_FIELD(TODO, custom_strike);
        DTO_FIELD(String, event_ticker);
        DTO_FIELD(DateTime_Iso8601, expected_expiration_time);
        DTO_FIELD(DateTime_Iso8601, expiration_time);
        DTO_FIELD(String, expiration_value);
        DTO_FIELD(DateTime_Iso8601, fee_waiver_expiration_time);
        DTO_FIELD(Float64, floor_strike);
        DTO_FIELD(String, functional_strike);
        DTO_FIELD(Int64, last_price);
        DTO_FIELD(DateTime_Iso8601, latest_expiration_time);
        DTO_FIELD(Int64, liquidity);
        DTO_FIELD(String, market_type);
        DTO_FIELD(Int64, no_ask);
        DTO_FIELD(Int64, no_bid);
        DTO_FIELD(String, no_sub_title);
        DTO_FIELD(Int64, notional_value);
        DTO_FIELD(Int64, open_interest);
        DTO_FIELD(DateTime_Iso8601, open_time);
        DTO_FIELD(Int64, previous_price);
        DTO_FIELD(Int64, previous_yes_ask);
        DTO_FIELD(Int64, previous_yes_bid);
        DTO_FIELD(String, response_price_units);
        DTO_FIELD(String, result);
        DTO_FIELD(Int64, risk_limit_cents);
        DTO_FIELD(String, rules_primary);
        DTO_FIELD(String, rules_secondary);
        DTO_FIELD(Int32, settlement_timer_seconds);
        DTO_FIELD(Int64, settlement_value);
        DTO_FIELD(String, status);
        DTO_FIELD(String, strike_type);
        //DTO_FIELD(String, subtitle); // DEPRECATED
        DTO_FIELD(Int64, tick_size);
        DTO_FIELD(String, ticker);
        DTO_FIELD(String, title);
        DTO_FIELD(Int64, volume);
        DTO_FIELD(Int64, volume_24h);
        DTO_FIELD(Int64, yes_ask);
        DTO_FIELD(Int64, yes_bid);
        DTO_FIELD(String, yes_sub_title);

    };

    struct Event
        : public oatpp::DTO
    {

        DTO_INIT(Event, DTO /* extends */)

        //DTO_FIELD(String, category); // DEPRECATED
        DTO_FIELD(String, event_ticker);
        DTO_FIELD(List<Object<Market>>, markets);
        DTO_FIELD(Boolean, mutually_exclusive);
        DTO_FIELD(String, series_ticker);
        DTO_FIELD(DateTime_Iso8601, strike_date);
        DTO_FIELD(String, strike_period);
        DTO_FIELD(String, sub_title);
        DTO_FIELD(String, title);

    };

    struct EventsResponse
        : public oatpp::DTO
    {

        DTO_INIT(EventsResponse, DTO /* extends */)

        DTO_FIELD(String, cursor);
        DTO_FIELD(List<Object<Event>>, events);

    };

    struct EventResponse
        : public oatpp::DTO
    {

        DTO_INIT(EventResponse, DTO /* extends */)

        DTO_FIELD(Object<Event>, event);

    };

    struct MarketsResponse
        : public oatpp::DTO
    {

        DTO_INIT(MarketsResponse, DTO /* extends */)

        DTO_FIELD(String, cursor);
        DTO_FIELD(List<Object<Market>>, markets);

    };

    struct MarketsRequest
        : public oatpp::DTO
    {

        DTO_INIT(MarketsRequest, DTO /* extends */)

        DTO_FIELD(String, cursor);
        DTO_FIELD(Int32, limit);
        DTO_FIELD(String, event_ticker);
        DTO_FIELD(String, series_ticker);
        DTO_FIELD(Int64, max_close_ts);
        DTO_FIELD(Int64, min_close_ts);
        DTO_FIELD(String, status);
        DTO_FIELD(String, tickers);

    };

    struct Trade
        : public oatpp::DTO
    {

        DTO_INIT(Trade, DTO /* extends */)

        DTO_FIELD(Int32, count);
        DTO_FIELD(DateTime_Iso8601, created_time);
        DTO_FIELD(Int64, no_price);
        DTO_FIELD(String, taker_side);
        DTO_FIELD(String, ticker);
        DTO_FIELD(String, trade_id);
        DTO_FIELD(Int64, yes_price);

    };

    struct TradesResponse
        : public oatpp::DTO
    {

        DTO_INIT(TradesResponse, DTO /* extends */)

        DTO_FIELD(String, cursor);
        DTO_FIELD(List<Object<Trade>>, trades);

    };

    struct TradesRequest
        : public oatpp::DTO
    {

        DTO_INIT(TradesRequest, DTO /* extends */)

        DTO_FIELD(String, cursor);
        DTO_FIELD(Int32, limit);
        DTO_FIELD(String, ticker);
        DTO_FIELD(Int64, min_ts);
        DTO_FIELD(Int64, max_ts);

    };

    struct MarketResponse
        : public oatpp::DTO
    {

        DTO_INIT(MarketResponse, DTO /* extends */)

        DTO_FIELD(Object<Market>, market);

    };

    struct MarketOrderbook
        : public oatpp::DTO
    {

        DTO_INIT(MarketOrderbook, DTO /* extends */)

        DTO_FIELD(List<Int32>, no);
        DTO_FIELD(List<Int32>, yes);

    };

    struct MarketOrderbookResponse
        : public oatpp::DTO
    {

        DTO_INIT(MarketOrderbookResponse, DTO /* extends */)

        DTO_FIELD(Object<MarketOrderbook>, orderbook);

    };

    struct SettlementSource
        : public oatpp::DTO
    {

        DTO_INIT(SettlementSource, DTO /* extends */)

        DTO_FIELD(String, name);
        DTO_FIELD(String, url);

    };

    struct Series
        : public oatpp::DTO
    {

        DTO_INIT(Series, DTO /* extends */)

        DTO_FIELD(String, category);
        DTO_FIELD(String, contract_url);
        DTO_FIELD(String, frequency);
        DTO_FIELD(List<Object<SettlementSource>>, settlement_sources);
        DTO_FIELD(List<String>, tags);
        DTO_FIELD(String, ticker);
        DTO_FIELD(String, title);

    };

    struct SeriesResponse
        : public oatpp::DTO
    {

        DTO_INIT(SeriesResponse, DTO /* extends */)

        DTO_FIELD(Int32, series);

    };

    struct Price
        : public oatpp::DTO
    {

        DTO_INIT(Price, DTO /* extends */)

        DTO_FIELD(Int64, close);
        DTO_FIELD(Int64, high);
        DTO_FIELD(Int64, low);
        DTO_FIELD(Int64, mean);
        DTO_FIELD(Int64, open);
        DTO_FIELD(Int64, previous);

    };

    struct YesAsk
        : public oatpp::DTO
    {

        DTO_INIT(YesAsk, DTO /* extends */)

        DTO_FIELD(Int64, close);
        DTO_FIELD(Int64, high);
        DTO_FIELD(Int64, low);
        DTO_FIELD(Int64, open);

    };

    struct YesBid
        : public oatpp::DTO
    {

        DTO_INIT(YesBid, DTO /* extends */)

        DTO_FIELD(Int64, close);
        DTO_FIELD(Int64, high);
        DTO_FIELD(Int64, low);
        DTO_FIELD(Int64, open);

    };

    struct MarketCandlestick
        : public oatpp::DTO
    {

        DTO_INIT(MarketCandlestick, DTO /* extends */)

        DTO_FIELD(Int64, end_period_ts);
        DTO_FIELD(Int64, open_interest);
        DTO_FIELD(Object<Price>, price);
        DTO_FIELD(Int64, volume);
        DTO_FIELD(Object<YesAsk>, yes_ask);
        DTO_FIELD(Object<YesBid>, yes_bid);
        DTO_FIELD(String, ticker);

    };

    struct MarketCandlesticksResponse
        : public oatpp::DTO
    {

        DTO_INIT(MarketCandlesticksResponse, DTO /* extends */)

        DTO_FIELD(Int64, start_ts);
        DTO_FIELD(Int64, end_ts);
        DTO_FIELD(Int32, period_interval);

    };

    // portfolio ////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////

    class BalanceResponse
        : public oatpp::DTO
    {

        DTO_INIT(BalanceResponse, DTO /* extends */)

        DTO_FIELD(Int64, balance);
        //TODO how to make optional?
        DTO_FIELD(Int64, payout);

    };

    class FillsRequest
        : public oatpp::DTO
    {

        DTO_INIT(FillsRequest, DTO /* extends */)

        DTO_FIELD(String, ticker);
        DTO_FIELD(String, order_id);
        DTO_FIELD(Int64, min_ts);
        DTO_FIELD(Int64, max_ts);
        DTO_FIELD(Int32, limit);
        DTO_FIELD(String, cursor);

    };

    class Fill
        : public oatpp::DTO
    {

        DTO_INIT(Fill, DTO /* extends */)

        DTO_FIELD(String, action);
        DTO_FIELD(Int32, count);
        DTO_FIELD(DateTime_Iso8601, created_time);
        DTO_FIELD(Boolean, is_taker);
        DTO_FIELD(Int64, no_price);
        DTO_FIELD(String, order_id);
        DTO_FIELD(String, side);
        DTO_FIELD(String, ticker);
        DTO_FIELD(Int64, yes_price);

    };

    class FillsResponse
        : public oatpp::DTO
    {

        DTO_INIT(FillsResponse, DTO /* extends */)

        DTO_FIELD(String, cursor);
        DTO_FIELD(Object<Fill>, fills);

    };

    class OrdersRequest
        : public oatpp::DTO
    {

        DTO_INIT(OrdersRequest, DTO /* extends */)

        DTO_FIELD(String, ticker);
        DTO_FIELD(String, event_ticker);
        DTO_FIELD(Int64, min_ts);
        DTO_FIELD(Int64, max_ts);
        DTO_FIELD(String, status);
        DTO_FIELD(String, cursor);
        DTO_FIELD(Int32, limit);

    };

    class Order
        : public oatpp::DTO
    {

        DTO_INIT(Order, DTO /* extends */)

        DTO_FIELD(String, action);
        DTO_FIELD(Int32, amend_count);
        DTO_FIELD(Int32, amend_taker_fill_count);
        DTO_FIELD(String, client_order_id);
        DTO_FIELD(Int32, close_cancel_count);
        DTO_FIELD(DateTime_Iso8601, created_time);
        DTO_FIELD(Int32, decrease_count);
        DTO_FIELD(DateTime_Iso8601, expiration_time);
        DTO_FIELD(Int32, fcc_cancel_count);
        DTO_FIELD(DateTime_Iso8601, last_update_time);
        DTO_FIELD(Int64, maker_fees);
        DTO_FIELD(Int64, maker_fill_cost);
        DTO_FIELD(Int32, maker_fill_count);
        DTO_FIELD(Int64, no_price);
        DTO_FIELD(String, order_id);
        DTO_FIELD(Int32, place_count);
        DTO_FIELD(Int32, queue_position);
        DTO_FIELD(Int32, remaining_count);
        DTO_FIELD(String, side);
        DTO_FIELD(String, status);
        DTO_FIELD(Int64, taker_fees);
        DTO_FIELD(Int64, taker_fill_cost);
        DTO_FIELD(Int32, taker_fill_count);
        DTO_FIELD(Int32, taker_self_trade_cancel_count);
        DTO_FIELD(String, ticker);
        DTO_FIELD(String, type);
        DTO_FIELD(String, user_id);
        DTO_FIELD(Int64, yes_price);

    };

    class OrdersResponse
        : public oatpp::DTO
    {

        DTO_INIT(OrdersResponse, DTO /* extends */)

        DTO_FIELD(String, cursor);
        DTO_FIELD(List<Object<Order>>, orders);

    };

    class CreateOrderRequest
        : public oatpp::DTO
    {

        DTO_INIT(CreateOrderRequest, DTO /* extends */)

        DTO_FIELD(String, action);
        DTO_FIELD(Int64, buy_max_cost);
        DTO_FIELD(String, client_order_id);
        DTO_FIELD(Int32, count);
        DTO_FIELD(Int64, expiration_ts);
        DTO_FIELD(Int64, no_price);
        DTO_FIELD(Int32, sell_position_floor);
        DTO_FIELD(String, side);
        DTO_FIELD(String, ticker);
        DTO_FIELD(String, type);
        DTO_FIELD(Int64, yes_price);

    };

    class OrderResponse
        : public oatpp::DTO
    {

        DTO_INIT(OrderResponse, DTO /* extends */)

        DTO_FIELD(Object<Order>, order);

    };

    class CancelOrderResponse
        : public oatpp::DTO
    {

        DTO_INIT(CancelOrderResponse, DTO /* extends */)

        DTO_FIELD(Object<Order>, order);
        DTO_FIELD(Int32, reduced_by);

    };

    class AmendOrderRequest
        : public oatpp::DTO
    {

        DTO_INIT(AmendOrderRequest, DTO /* extends */)

        DTO_FIELD(String, action);
        DTO_FIELD(String, client_order_id);
        DTO_FIELD(Int32, count);
        DTO_FIELD(Int64, no_price);
        DTO_FIELD(String, side);
        DTO_FIELD(String, ticker);
        DTO_FIELD(String, updated_client_order_id);
        DTO_FIELD(Int64, yes_price);

    };

    class AmendOrderResponse
        : public oatpp::DTO
    {

        DTO_INIT(AmendOrderResponse, DTO /* extends */)

        DTO_FIELD(Object<Order>, old_order);
        DTO_FIELD(Object<Order>, order);

    };

    class DecreaseOrderRequest
        : public oatpp::DTO
    {

        DTO_INIT(DecreaseOrderRequest, DTO /* extends */)

        DTO_FIELD(Int32, reduce_by);
        DTO_FIELD(Int32, reduce_to);

    };

    struct PositionsRequest
        : public oatpp::DTO
    {

        DTO_INIT(PositionsRequest, DTO /* extends */)

        DTO_FIELD(String, cursor);
        DTO_FIELD(Int32, limit);
        DTO_FIELD(String, count_filter);
        DTO_FIELD(String, settlement_status);
        DTO_FIELD(String, ticker);
        DTO_FIELD(String, event_ticker);

    };

    class EventPosition
        : public oatpp::DTO
    {

        DTO_INIT(EventPosition, DTO /* extends */)

        DTO_FIELD(Int64, event_exposure);
        DTO_FIELD(String, event_ticker);
        DTO_FIELD(Int64, fees_paid);
        DTO_FIELD(Int64, realized_pnl);
        DTO_FIELD(Int32, resting_order_count);
        DTO_FIELD(Int64, total_cost);

    };

    class MarketPosition
        : public oatpp::DTO
    {

        DTO_INIT(MarketPosition, DTO /* extends */)

        DTO_FIELD(Int64, fees_paid);
        DTO_FIELD(Int64, market_exposure);
        DTO_FIELD(Int32, position);
        DTO_FIELD(Int64, realized_pnl);
        DTO_FIELD(Int32, resting_orders_count);
        DTO_FIELD(String, ticker);
        DTO_FIELD(Int64, total_traded);

    };

    struct PositionsResponse
        : public oatpp::DTO
    {

        DTO_INIT(PositionsResponse, DTO /* extends */)

        DTO_FIELD(String, cursor);
        DTO_FIELD(List<Object<EventPosition>>, event_positions);
        DTO_FIELD(List<Object<MarketPosition>>, market_positions);

    };

    class Settlement
        : public oatpp::DTO
    {

        DTO_INIT(Settlement, DTO /* extends */)

        DTO_FIELD(String, market_result);
        DTO_FIELD(Int64, no_count);
        DTO_FIELD(Int64, no_total_cost);
        DTO_FIELD(Int64, revenue);
        DTO_FIELD(DateTime_Iso8601, settled_time);
        DTO_FIELD(String, ticker);
        DTO_FIELD(Int64, yes_count);
        DTO_FIELD(Int64, yes_total_cost);

    };

    class PortfolioSettlementsResponse
        : public oatpp::DTO
    {

        DTO_INIT(PortfolioSettlementsResponse, DTO /* extends */)

        DTO_FIELD(String, cursor);
        DTO_FIELD(Object<Settlement>, settlements);

    };

    #include OATPP_CODEGEN_END(DTO)

}

#endif
