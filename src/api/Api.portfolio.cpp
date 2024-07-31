#include <memory>
#include <stdexcept>
#include <string_view>

#include "api/Api.hpp"
#include "api/types.hpp"

namespace kdeck
{

    double Api::GetBalance()
    {
        OATPP_LOGD("Api", "GetBalance");

        ApiResult<BalanceResponse> res = HandleResponse<BalanceResponse>(_api->GetBalance(userAgent, basePath, login->token));

        if (std::holds_alternative<std::shared_ptr<BalanceResponse>>(res))
        {
            balance = std::get<std::shared_ptr<BalanceResponse>>(res);
        }
        else
        {
            throw std::runtime_error(std::get<std::shared_ptr<ErrorResponse>>(res)->error->message->c_str());
        }

        return balance->balance;
    }

    std::shared_ptr<OrdersResponse> Api::GetOrders()
    {
        OATPP_LOGD("Api", "GetOrders");

        auto req = OrdersRequest::createShared();

        ApiResult<OrdersResponse> res = HandleResponse<OrdersResponse>(_api->GetOrders(userAgent, basePath, login->token, req));

        if (std::holds_alternative<std::shared_ptr<OrdersResponse>>(res))
        {
            //TODO populate orders
            return std::get<std::shared_ptr<OrdersResponse>>(res);
        }
        else
        {
            throw std::runtime_error(std::get<std::shared_ptr<ErrorResponse>>(res)->error->message->c_str());
        }

        //TODO return orders;
    }

    std::shared_ptr<OrderResponse> Api::CreateOrder()
    {
        OATPP_LOGD("Api", "CreateOrder");

        auto req = CreateOrderRequest::createShared();

        ApiResult<OrderResponse> res = HandleResponse<OrderResponse>(_api->CreateOrder(userAgent, basePath, login->token, req));

        if (std::holds_alternative<std::shared_ptr<OrderResponse>>(res))
        {
            //TODO populate orders
            return std::get<std::shared_ptr<OrderResponse>>(res);
        }
        else
        {
            throw std::runtime_error(std::get<std::shared_ptr<ErrorResponse>>(res)->error->message->c_str());
        }

        //TODO return order;
    }

    std::shared_ptr<OrderResponse> Api::GetOrder(std::string_view orderId)
    {
        OATPP_LOGD("Api", "GetOrder");

        ApiResult<OrderResponse> res = HandleResponse<OrderResponse>(_api->GetOrder(userAgent, basePath, login->token, std::string{orderId}));

        if (std::holds_alternative<std::shared_ptr<OrderResponse>>(res))
        {
            //TODO populate orders
            return std::get<std::shared_ptr<OrderResponse>>(res);
        }
        else
        {
            throw std::runtime_error(std::get<std::shared_ptr<ErrorResponse>>(res)->error->message->c_str());
        }

        //TODO return order;
    }

    std::shared_ptr<CancelOrderResponse> Api::CancelOrder(std::string_view orderId)
    {
        OATPP_LOGD("Api", "CancelOrder");

        ApiResult<CancelOrderResponse> res = HandleResponse<CancelOrderResponse>(_api->CancelOrder(userAgent, basePath, login->token, std::string{orderId}));

        if (std::holds_alternative<std::shared_ptr<CancelOrderResponse>>(res))
        {
            //TODO depopulate orders; this can return a partially filled order!
            return std::get<std::shared_ptr<CancelOrderResponse>>(res);
        }
        else
        {
            throw std::runtime_error(std::get<std::shared_ptr<ErrorResponse>>(res)->error->message->c_str());
        }

        //TODO return order;
    }

    std::shared_ptr<AmendOrderResponse> Api::AmendOrder(std::string_view orderId)
    {
        OATPP_LOGD("Api", "AmendOrder");

        auto req = AmendOrderRequest::createShared();

        ApiResult<AmendOrderResponse> res = HandleResponse<AmendOrderResponse>(_api->AmendOrder(userAgent, basePath, login->token, std::string{orderId}, req));

        if (std::holds_alternative<std::shared_ptr<AmendOrderResponse>>(res))
        {
            //TODO populate orders
            return std::get<std::shared_ptr<AmendOrderResponse>>(res);
        }
        else
        {
            throw std::runtime_error(std::get<std::shared_ptr<ErrorResponse>>(res)->error->message->c_str());
        }

        //TODO return order;
    }

    std::shared_ptr<OrderResponse> Api::DecreaseOrder(std::string_view orderId)
    {
        OATPP_LOGD("Api", "DecreaseOrder");

        auto req = DecreaseOrderRequest::createShared();

        ApiResult<OrderResponse> res = HandleResponse<OrderResponse>(_api->DecreaseOrder(userAgent, basePath, login->token, std::string{orderId}, req));

        if (std::holds_alternative<std::shared_ptr<OrderResponse>>(res))
        {
            //TODO populate orders
            return std::get<std::shared_ptr<OrderResponse>>(res);
        }
        else
        {
            throw std::runtime_error(std::get<std::shared_ptr<ErrorResponse>>(res)->error->message->c_str());
        }

        //TODO return order;
    }

    std::shared_ptr<PositionsResponse> Api::GetPositions()
    {
        OATPP_LOGD("Api", "GetPositions");

        auto req = PositionsRequest::createShared();

        ApiResult<PositionsResponse> res = HandleResponse<PositionsResponse>(_api->GetPositions(userAgent, basePath, login->token, req));

        if (std::holds_alternative<std::shared_ptr<PositionsResponse>>(res))
        {
            positions = std::get<std::shared_ptr<PositionsResponse>>(res);

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

    std::shared_ptr<PortfolioSettlementsResponse> Api::GetPortfolioSettlements()
    {
        OATPP_LOGD("Api", "GetPortfolioSettlements");

        auto req = PortfolioSettlementsRequest::createShared();

        ApiResult<PortfolioSettlementsResponse> res = HandleResponse<PortfolioSettlementsResponse>(_api->GetPortfolioSettlements(userAgent, basePath, login->token, req));

        if (std::holds_alternative<std::shared_ptr<PortfolioSettlementsResponse>>(res))
        {
            //TODO populate settlements
            return std::get<std::shared_ptr<PortfolioSettlementsResponse>>(res);
        }
        else
        {
            throw std::runtime_error(std::get<std::shared_ptr<ErrorResponse>>(res)->error->message->c_str());
        }

        //TODO return settlements;
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
