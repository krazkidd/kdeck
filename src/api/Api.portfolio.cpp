#include <string>
#include <string_view>
#include <stdexcept>
#include <vector>

#include <boost/json.hpp>

#include "api/Api.hpp"
#include "api/converters.hpp"
#include "api/types.hpp"

double Api::GetBalance()
{
    if (!IsLoggedIn())
    {
        throw std::logic_error("Not logged in.");
    }

    balance = GetRequest<PortfolioBalanceResponse>("/portfolio/balance");

    return balance.balance;
}

std::vector<PortfolioPositionsResponse::MarketPosition> Api::GetPositions()
{
    if (!IsLoggedIn())
    {
        throw std::logic_error("Not logged in.");
    }

    positions = GetRequest<PortfolioPositionsResponse>("/portfolio/positions");

    return positions.market_positions;
}
