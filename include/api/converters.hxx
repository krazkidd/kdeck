#include <boost/json.hpp>

#include "api/types.hpp"

inline VoidResponse tag_invoke(const boost::json::value_to_tag<VoidResponse> &, const boost::json::value &jv)
{
    if (auto jo = jv.is_null())
    {
        return VoidResponse{};
    }
    else
    {
        throw std::runtime_error("Invalid JSON response.");
    }
}

inline ErrorResponse tag_invoke(const boost::json::value_to_tag<ErrorResponse> &, const boost::json::value &jv)
{
    if (auto jo = jv.if_object())
    {
        return ErrorResponse{
            jo->at("code").as_string().c_str(),
            //TODO try using std::optional and null coalescence
            //jo->at("details").as_string().c_str(),
            jo->at("message").as_string().c_str()
        };
    }
    else
    {
        throw std::runtime_error("Invalid JSON response.");
    }
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
    if (auto jo = jv.if_object())
    {
        return LoginResponse{
            jo->at("member_id").as_string().c_str(),
            jo->at("token").as_string().c_str()
        };
    }
    else
    {
        throw std::runtime_error("Invalid JSON response.");
    }
}

inline PortfolioBalanceResponse tag_invoke(const boost::json::value_to_tag<PortfolioBalanceResponse> &, const boost::json::value &jv)
{
    if (auto jo = jv.if_object())
    {
        return PortfolioBalanceResponse{
            jo->at("balance").as_int64() / 100.0,
            //TODO try using std::optional and null coalescence
            //jo->at("payout").as_int64() / 100.0
        };
    }
    else
    {
        throw std::runtime_error("Invalid JSON response.");
    }
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
    if (auto jo = jv.if_object())
    {
        return PortfolioPositionsResponse::EventPosition{
            jo->at("event_exposure").as_int64() / 100.0,
            jo->at("event_ticker").as_string().c_str(),
            jo->at("fees_paid").as_int64() / 100.0,
            jo->at("realized_pnl").as_int64() / 100.0,
            jo->at("resting_order_count").as_int64(),
            jo->at("total_cost").as_int64() / 100.0
        };
    }
    else
    {
        throw std::runtime_error("Invalid JSON response.");
    }
}

inline PortfolioPositionsResponse::MarketPosition tag_invoke(const boost::json::value_to_tag<PortfolioPositionsResponse::MarketPosition> &, const boost::json::value &jv)
{
    if (auto jo = jv.if_object())
    {
        return PortfolioPositionsResponse::MarketPosition{
            jo->at("fees_paid").as_int64() / 100.0,
            jo->at("market_exposure").as_int64() / 100.0,
            jo->at("position").as_int64(),
            jo->at("realized_pnl").as_int64() / 100.0,
            jo->at("resting_orders_count").as_int64(),
            jo->at("ticker").as_string().c_str(),
            jo->at("total_traded").as_int64() / 100.0
        };
    }
    else
    {
        throw std::runtime_error("Invalid JSON response.");
    }
}

inline PortfolioPositionsResponse tag_invoke(const boost::json::value_to_tag<PortfolioPositionsResponse> &, const boost::json::value &jv)
{
    if (auto jo = jv.if_object())
    {
        boost::json::array event_positions = jo->at("event_positions").as_array();
        boost::json::array market_positions = jo->at("market_positions").as_array();

        std::vector<PortfolioPositionsResponse::EventPosition> eventPositions;
        std::vector<PortfolioPositionsResponse::MarketPosition> marketPositions;

        eventPositions.reserve(event_positions.size());
        marketPositions.reserve(market_positions.size());

        for (boost::json::value val : event_positions)
        {
            eventPositions.push_back(boost::json::value_to<PortfolioPositionsResponse::EventPosition>(val));
        }

        for (boost::json::value val : market_positions)
        {
            marketPositions.push_back(boost::json::value_to<PortfolioPositionsResponse::MarketPosition>(val));
        }

        return PortfolioPositionsResponse{
            jo->at("cursor").as_string().c_str(),
            eventPositions,
            marketPositions
        };
    }
    else
    {
        throw std::runtime_error("Invalid JSON response.");
    }
}