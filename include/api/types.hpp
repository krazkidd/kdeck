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

    #include OATPP_CODEGEN_END(DTO)

    // exchange /////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////

    struct ExchangeAnnouncementsResponse
    {
        struct Announcement
        {
            std::chrono::time_point<std::chrono::system_clock> delivery_time{};
            std::string message{};
            std::string status{};
            std::string type{};
        };

        std::vector<Announcement> announcements{};
    };

    struct ExchangeScheduleResponse
    {
        struct MaintenanceWindow
        {
            std::chrono::time_point<std::chrono::system_clock> start_datetime{};
            std::chrono::time_point<std::chrono::system_clock> end_datetime{};
        };

        struct DailyHours
        {
            std::string open_time{};
            std::string close_time{};
        };

        struct StandardHours
        {
            DailyHours sunday{};
            DailyHours monday{};
            DailyHours tuesday{};
            DailyHours wednesday{};
            DailyHours thursday{};
            DailyHours friday{};
            DailyHours saturday{};
        };

        struct Schedule
        {
            std::vector<MaintenanceWindow> maintenance_windows{};
            StandardHours standard_hours{};
        };

        Schedule schedule{};
    };

    struct ExchangeStatusResponse
    {
        bool exchange_active{};
        bool trading_active{};
    };

    // portfolio ////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////

    struct PortfolioBalanceResponse
    {
        double balance{};
        //TODO try using std::optional
        double payout{};
    };

    struct PortfolioPositionsRequest
    {
        std::string_view cursor{};
        int limit{100};
        std::string_view count_filter{"position,total_traded,resting_order_count"};
        std::string_view settlement_status{"unsettled"};
        std::string_view ticker{};
        std::string_view event_ticker{};
    };

    struct PortfolioPositionsResponse
    {
        struct EventPosition
        {
            double event_exposure{};
            std::string event_ticker{};
            double fees_paid{};
            double realized_pnl{};
            long resting_order_count{};
            double total_cost{};
        };

        struct MarketPosition
        {
            double fees_paid{};
            double market_exposure{};
            long position{};
            double realized_pnl{};
            long resting_orders_count{};
            std::string ticker{};
            double total_traded{};
        };

        std::string cursor{};
        std::vector<EventPosition> event_positions{};
        std::vector<MarketPosition> market_positions{};
    };
}

#endif
