#include <stdexcept>
#include <string_view>
#include <variant>
#include <vector>

#include "api/Api.hpp"
#include "api/types.hpp"

namespace kdeck
{
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

            eventsMap.clear();
            marketsMap.clear();

            for (const auto &event : positions.event_positions)
            {
                eventsMap[event.event_ticker] = event;
            }

            for (const auto &market : positions.market_positions)
            {
                std::string eventTicker = market.ticker.substr(0, market.ticker.find("-"));

                if (marketsMap.find(eventTicker) == marketsMap.end())
                {
                    marketsMap[eventTicker] = {};
                }

                marketsMap[eventTicker][market.ticker] = market;
            }
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

    std::vector<PortfolioPositionsResponse::MarketPosition> Api::GetMarketPositions(std::string_view eventTicker)
    {
        if (eventTicker.empty())
        {
            return positions.market_positions;
        }

        //TODO we should probably check if the eventTicker is in the map
        const auto map = marketsMap[std::string{eventTicker}];

        //TODO creating a vector is not very efficient--can we just return an iterator (using a lambda)?
        std::vector<PortfolioPositionsResponse::MarketPosition> vec;
        vec.reserve(map.size());

        for (const auto &pair : map)
        {
            //TODO this is dangerous because we are not making a copy
            vec.push_back(pair.second);
        }

        return vec;
    }
}
