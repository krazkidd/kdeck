#include <chrono>

#include <boost/json.hpp>

#include "api/types.hpp"

namespace kdeck
{
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
}
