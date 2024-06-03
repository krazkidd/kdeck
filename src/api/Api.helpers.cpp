#include "api/Api.h"

bool Api::IsLoggedIn()
{
    return !login.member_id.empty();
}

std::vector<PortfolioPositionsResponse::EventPosition> Api::GetEventPositions()
{
    return positions.event_positions;
}

std::vector<PortfolioPositionsResponse::MarketPosition> Api::GetMarketPositions()
{
    return positions.market_positions;
}
