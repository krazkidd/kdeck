#include <stdexcept>
#include <variant>
#include <vector>

#include "api/Api.hpp"
#include "api/types.hpp"

double Api::GetBalance()
{
    if (!IsLoggedIn())
    {
        throw std::logic_error("Not logged in.");
    }

    ApiResult<PortfolioBalanceResponse> res = GetRequest<PortfolioBalanceResponse>("/portfolio/balance");

    if (std::holds_alternative<PortfolioBalanceResponse>(res))
    {
        balance = std::get<PortfolioBalanceResponse>(res);
    }
    else
    {
        throw std::runtime_error(std::get<ErrorResponse>(res).message);
    }

    return balance.balance;
}

PortfolioPositionsResponse Api::GetPositions()
{
    if (!IsLoggedIn())
    {
        throw std::logic_error("Not logged in.");
    }

    ApiResult<PortfolioPositionsResponse> res = GetRequest<PortfolioPositionsResponse>("/portfolio/positions");

    if (std::holds_alternative<PortfolioPositionsResponse>(res))
    {
        positions = std::get<PortfolioPositionsResponse>(res);
    }
    else
    {
        throw std::runtime_error(std::get<ErrorResponse>(res).message);
    }

    return positions;
}

// helpers /////////////////////////////////////////////////////////////////////

std::vector<PortfolioPositionsResponse::EventPosition> Api::GetEventPositions()
{
    return positions.event_positions;
}

std::vector<PortfolioPositionsResponse::MarketPosition> Api::GetMarketPositions()
{
    return positions.market_positions;
}
