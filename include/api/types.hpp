#ifndef TYPES_HPP
#define TYPES_HPP

#include <chrono>
#include <string>
#include <string_view>
#include <vector>

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

namespace kdeck
{
    struct VoidResponse
    {

    };

    struct ErrorResponse
    {
        std::string code{};
        //TODO try using std::optional
        std::string details{};
        std::string message{};
    };

    #include OATPP_CODEGEN_BEGIN(DTO)

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

        //TODO
        //std::chrono::time_point<std::chrono::system_clock> delivery_time{};
        //DTO_FIELD(TODO, delivery_time);
        DTO_FIELD(String, message);
        DTO_FIELD(String, status);
        DTO_FIELD(String, type);

    };

    class MaintenanceWindow
        : public oatpp::DTO
    {

        DTO_INIT(MaintenanceWindow, DTO /* extends */)

        //TODO
        //std::chrono::time_point<std::chrono::system_clock> start_datetime{};
        //DTO_FIELD(TODO, start_datetime);
        //TODO
        //std::chrono::time_point<std::chrono::system_clock> end_datetime{};
        //DTO_FIELD(TODO, end_datetime);

    };

    class DailyHours
        : public oatpp::DTO
    {

        DTO_INIT(DailyHours, DTO /* extends */)

        DTO_FIELD(String, open_time);
        DTO_FIELD(String, close_time);

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

    // portfolio ////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////

    class PortfolioBalanceResponse
        : public oatpp::DTO
    {
        DTO_INIT(PortfolioBalanceResponse, DTO /* extends */)

        DTO_FIELD(Int64, balance);
        //TODO how to make optional?
        DTO_FIELD(Int64, payout);

    };

    struct PortfolioPositionsRequest
        : public oatpp::DTO
    {

        DTO_INIT(PortfolioPositionsRequest, DTO /* extends */)

        DTO_FIELD(String, cursor);
        DTO_FIELD(Int32, limit) = 100;
        DTO_FIELD(String, count_filter) = "position,total_traded,resting_order_count";
        DTO_FIELD(String, settlement_status) = "unsettled";
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

    struct PortfolioPositionsResponse
        : public oatpp::DTO
    {

        DTO_INIT(PortfolioPositionsResponse, DTO /* extends */)

        DTO_FIELD(String, cursor);
        DTO_FIELD(List<Object<EventPosition>>, event_positions);
        DTO_FIELD(List<Object<MarketPosition>>, market_positions);

    };

    #include OATPP_CODEGEN_END(DTO)

}

#endif
