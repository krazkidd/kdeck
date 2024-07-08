#include <memory>
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

        OATPP_LOGD("Api", "GetBalance");

        ApiResult<PortfolioBalanceResponse> res = HandleResponse<PortfolioBalanceResponse>(_api->GetBalance(basePath, login->token));

        if (std::holds_alternative<std::shared_ptr<PortfolioBalanceResponse>>(res))
        {
            balance = std::get<std::shared_ptr<PortfolioBalanceResponse>>(res);
        }
        else
        {
            throw std::runtime_error(std::get<std::shared_ptr<ErrorResponse>>(res)->error->message->c_str());
        }

        return balance->balance;
    }

    std::shared_ptr<PortfolioPositionsResponse> Api::GetPositions()
    {
        if (!IsLoggedIn())
        {
            throw std::logic_error("Not logged in.");
        }

        OATPP_LOGD("Api", "GetPositions");

        auto req = PortfolioPositionsRequest::createShared();

        ApiResult<PortfolioPositionsResponse> res = HandleResponse<PortfolioPositionsResponse>(_api->GetPositions(basePath, login->token, req));

        if (std::holds_alternative<std::shared_ptr<PortfolioPositionsResponse>>(res))
        {
            positions = std::get<std::shared_ptr<PortfolioPositionsResponse>>(res);

            eventsMap.clear();
            marketsMap.clear();

            for (const auto event : *positions->event_positions)
            {
                eventsMap[*event->event_ticker] = event.getPtr();
            }

            for (const auto market : *positions->market_positions)
            {
                std::string eventTicker = market->ticker->substr(0, market->ticker->find("-"));

                if (marketsMap.count(eventTicker) == 0)
                {
                    marketsMap[eventTicker] = {};
                }

                marketsMap[eventTicker][*market->ticker] = market.getPtr();
            }
        }
        else
        {
            throw std::runtime_error(std::get<std::shared_ptr<ErrorResponse>>(res)->error->message->c_str());
        }

        return positions;
    }

    // helpers /////////////////////////////////////////////////////////////////////

    std::list<std::shared_ptr<EventPosition>> Api::GetEventPositions()
    {
        //TODO try to avoid creating a new list

        auto list = std::list<std::shared_ptr<EventPosition>>();

        for (const auto event : *positions->event_positions)
        {
            list.emplace_back(event.getPtr());
        }

        return list;
    }

    std::list<std::shared_ptr<MarketPosition>> Api::GetMarketPositions(std::string_view eventTicker)
    {
        //TODO try to avoid creating a new list

        if (eventTicker.empty())
        {
            auto list = std::list<std::shared_ptr<MarketPosition>>();

            for (const auto market : *positions->market_positions)
            {
                list.emplace_back(market.getPtr());
            }

            return list;
        }

        //TODO we should probably check if the eventTicker is in the map
        const auto map = marketsMap[std::string{eventTicker}];

        auto list = std::list<std::shared_ptr<MarketPosition>>();

        for (const auto pair : map)
        {
            list.emplace_back(pair.second);
        }

        return list;
    }
}
