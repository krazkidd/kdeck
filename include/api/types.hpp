#ifndef TYPES_HPP
#define TYPES_HPP

#include <string>
#include <string_view>
#include <vector>

struct LoginRequest
{
    std::string_view email{};
    std::string_view password{};
};

struct LoginResponse
{
    std::string member_id{};
    std::string token{};
};

struct PortfolioBalanceResponse
{
    double balance{};
    //TODO try using std::optional and null coalescence
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

#endif