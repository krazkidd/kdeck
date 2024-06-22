#include <chrono>

#include <boost/json.hpp>

#include "api/types.hpp"

// we don't use this but it's required to compile
inline VoidResponse tag_invoke(const boost::json::value_to_tag<VoidResponse> &, const boost::json::value &jv)
{
    return VoidResponse{};
}

inline ErrorResponse tag_invoke(const boost::json::value_to_tag<ErrorResponse> &, const boost::json::value &jv)
{
    return ErrorResponse{
        jv.at("code").as_string().c_str(),
        //TODO try using std::optional
        //jo->at("details").as_string().c_str(),
        jv.at("message").as_string().c_str()
    };
}

inline void tag_invoke(const boost::json::value_from_tag &, boost::json::value &jv, const LoginRequest &req)
{
    jv = {
        { "email", req.email },
        { "password", req.password }
    };
}

inline LoginResponse tag_invoke(const boost::json::value_to_tag<LoginResponse> &, const boost::json::value &jv)
{
    return LoginResponse{
        jv.at("member_id").as_string().c_str(),
        jv.at("token").as_string().c_str()
    };
}

inline ExchangeAnnouncementsResponse::Announcement tag_invoke(const boost::json::value_to_tag<ExchangeAnnouncementsResponse::Announcement> &, const boost::json::value &jv)
{
    return ExchangeAnnouncementsResponse::Announcement{
        //TODO
        //std::chrono::time_point<std::chrono::system_clock>{jv.at("delivery_time")},
        std::chrono::time_point<std::chrono::system_clock>{},
        jv.at("message").as_string().c_str(),
        jv.at("status").as_string().c_str(),
        jv.at("type").as_string().c_str()
    };
}

inline ExchangeAnnouncementsResponse tag_invoke(const boost::json::value_to_tag<ExchangeAnnouncementsResponse> &, const boost::json::value &jv)
{
    return ExchangeAnnouncementsResponse{
        boost::json::value_to<std::vector<ExchangeAnnouncementsResponse::Announcement>>(jv.at("announcements")),
    };
}

inline ExchangeScheduleResponse::DailyHours tag_invoke(const boost::json::value_to_tag<ExchangeScheduleResponse::DailyHours> &, const boost::json::value &jv)
{
    return ExchangeScheduleResponse::DailyHours{
        jv.at("open_time").as_string().c_str(),
        jv.at("close_time").as_string().c_str()
    };
}

inline ExchangeScheduleResponse::StandardHours tag_invoke(const boost::json::value_to_tag<ExchangeScheduleResponse::StandardHours> &, const boost::json::value &jv)
{
    return ExchangeScheduleResponse::StandardHours{
        boost::json::value_to<ExchangeScheduleResponse::DailyHours>(jv.at("sunday")),
        boost::json::value_to<ExchangeScheduleResponse::DailyHours>(jv.at("monday")),
        boost::json::value_to<ExchangeScheduleResponse::DailyHours>(jv.at("tuesday")),
        boost::json::value_to<ExchangeScheduleResponse::DailyHours>(jv.at("wednesday")),
        boost::json::value_to<ExchangeScheduleResponse::DailyHours>(jv.at("thursday")),
        boost::json::value_to<ExchangeScheduleResponse::DailyHours>(jv.at("friday")),
        boost::json::value_to<ExchangeScheduleResponse::DailyHours>(jv.at("saturday"))
    };
}

inline ExchangeScheduleResponse::MaintenanceWindow tag_invoke(const boost::json::value_to_tag<ExchangeScheduleResponse::MaintenanceWindow> &, const boost::json::value &jv)
{
    return ExchangeScheduleResponse::MaintenanceWindow{
        //TODO
        //std::chrono::time_point<std::chrono::system_clock>{jv.at("start_datetime")},
        std::chrono::time_point<std::chrono::system_clock>{},
        //std::chrono::time_point<std::chrono::system_clock>{jv.at("end_datetime")}
        std::chrono::time_point<std::chrono::system_clock>{}
    };
}

inline ExchangeScheduleResponse::Schedule tag_invoke(const boost::json::value_to_tag<ExchangeScheduleResponse::Schedule> &, const boost::json::value &jv)
{
    return ExchangeScheduleResponse::Schedule{
        boost::json::value_to<std::vector<ExchangeScheduleResponse::MaintenanceWindow>>(jv.at("maintenance_windows")),
        boost::json::value_to<ExchangeScheduleResponse::StandardHours>(jv.at("standard_hours"))
    };
}

inline ExchangeScheduleResponse tag_invoke(const boost::json::value_to_tag<ExchangeScheduleResponse> &, const boost::json::value &jv)
{
    return ExchangeScheduleResponse{
        boost::json::value_to<ExchangeScheduleResponse::Schedule>(jv.at("schedule")),
    };
}

inline ExchangeStatusResponse tag_invoke(const boost::json::value_to_tag<ExchangeStatusResponse> &, const boost::json::value &jv)
{
    return ExchangeStatusResponse{
        jv.at("exchange_active").as_bool(),
        jv.at("trading_active").as_bool(),
    };
}

inline PortfolioBalanceResponse tag_invoke(const boost::json::value_to_tag<PortfolioBalanceResponse> &, const boost::json::value &jv)
{
    return PortfolioBalanceResponse{
        jv.at("balance").as_int64() / 100.0,
        //TODO try using std::optional
        //jv.at("payout").as_int64() / 100.0
    };
}

inline void tag_invoke(const boost::json::value_from_tag &, boost::json::value &jv, const PortfolioPositionsRequest &req)
{
    jv = {
        { "cursor", req.cursor },
        { "limit", req.limit },
        { "count_filter", req.count_filter },
        { "settlement_status", req.settlement_status },
        { "ticker", req.ticker },
        { "event_ticker", req.event_ticker }
    };
}

inline PortfolioPositionsResponse::EventPosition tag_invoke(const boost::json::value_to_tag<PortfolioPositionsResponse::EventPosition> &, const boost::json::value &jv)
{
    return PortfolioPositionsResponse::EventPosition{
        jv.at("event_exposure").as_int64() / 100.0,
        jv.at("event_ticker").as_string().c_str(),
        jv.at("fees_paid").as_int64() / 100.0,
        jv.at("realized_pnl").as_int64() / 100.0,
        jv.at("resting_order_count").as_int64(),
        jv.at("total_cost").as_int64() / 100.0
    };
}

inline PortfolioPositionsResponse::MarketPosition tag_invoke(const boost::json::value_to_tag<PortfolioPositionsResponse::MarketPosition> &, const boost::json::value &jv)
{
    return PortfolioPositionsResponse::MarketPosition{
        jv.at("fees_paid").as_int64() / 100.0,
        jv.at("market_exposure").as_int64() / 100.0,
        jv.at("position").as_int64(),
        jv.at("realized_pnl").as_int64() / 100.0,
        jv.at("resting_orders_count").as_int64(),
        jv.at("ticker").as_string().c_str(),
        jv.at("total_traded").as_int64() / 100.0
    };
}

inline PortfolioPositionsResponse tag_invoke(const boost::json::value_to_tag<PortfolioPositionsResponse> &, const boost::json::value &jv)
{
    return PortfolioPositionsResponse{
        jv.at("cursor").as_string().c_str(),
        boost::json::value_to<std::vector<PortfolioPositionsResponse::EventPosition>>(jv.at("event_positions")),
        boost::json::value_to<std::vector<PortfolioPositionsResponse::MarketPosition>>(jv.at("market_positions"))
    };
}