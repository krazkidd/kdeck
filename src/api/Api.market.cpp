#include <stdexcept>

#include "api/Api.hpp"
#include "api/types.hpp"

namespace kdeck
{

    std::shared_ptr<EventsResponse> Api::GetEvents()
    {
        OATPP_LOGD("Api", "GetEvents");

        auto req = EventsRequest::createShared();

        ApiResult<EventsResponse> res = HandleResponse<EventsResponse>(_api->GetEvents(userAgent, basePath, req->cursor, req->limit, req->status, req->series_ticker, req->with_nested_markets));

        if (std::holds_alternative<std::shared_ptr<EventsResponse>>(res))
        {
            events = std::get<std::shared_ptr<EventsResponse>>(res);
        }
        else
        {
            throw std::runtime_error(std::get<std::shared_ptr<ErrorResponse>>(res)->error->message->c_str());
        }

        return events;
    }

    std::shared_ptr<EventResponse> Api::GetEvent(std::string_view eventTicker)
    {
        OATPP_LOGD("Api", "GetEvent");

        ApiResult<EventResponse> res = HandleResponse<EventResponse>(_api->GetEvent(userAgent, basePath, std::string{eventTicker}, nullptr));

        if (std::holds_alternative<std::shared_ptr<EventResponse>>(res))
        {
            //TODO populate events
            return std::get<std::shared_ptr<EventResponse>>(res);
        }
        else
        {
            throw std::runtime_error(std::get<std::shared_ptr<ErrorResponse>>(res)->error->message->c_str());
        }

        //TODO return events[eventTicker];
    }

    std::shared_ptr<MarketsResponse> Api::GetMarkets()
    {
        OATPP_LOGD("Api", "GetMarkets");

        auto req = MarketsRequest::createShared();

        ApiResult<MarketsResponse> res = HandleResponse<MarketsResponse>(_api->GetMarkets(userAgent, basePath, login->token, req->cursor, req->limit, req->event_ticker, req->series_ticker, req->max_close_ts, req->min_close_ts, req->status, req->tickers));

        if (std::holds_alternative<std::shared_ptr<MarketsResponse>>(res))
        {
            markets = std::get<std::shared_ptr<MarketsResponse>>(res);
        }
        else
        {
            throw std::runtime_error(std::get<std::shared_ptr<ErrorResponse>>(res)->error->message->c_str());
        }

        return markets;
    }

    std::shared_ptr<TradesResponse> Api::GetTrades()
    {
        OATPP_LOGD("Api", "GetTrades");

        auto req = TradesRequest::createShared();

        ApiResult<TradesResponse> res = HandleResponse<TradesResponse>(_api->GetTrades(userAgent, basePath, req->cursor, req->limit, req->ticker, req->min_ts, req->max_ts));

        if (std::holds_alternative<std::shared_ptr<TradesResponse>>(res))
        {
            //TODO populate trades
            return std::get<std::shared_ptr<TradesResponse>>(res);
        }
        else
        {
            throw std::runtime_error(std::get<std::shared_ptr<ErrorResponse>>(res)->error->message->c_str());
        }

        //TODO return trades;
    }

    std::shared_ptr<MarketResponse> Api::GetMarket(std::string_view marketTicker)
    {
        OATPP_LOGD("Api", "GetMarket");

        ApiResult<MarketResponse> res = HandleResponse<MarketResponse>(_api->GetMarket(userAgent, basePath, std::string{marketTicker}));

        if (std::holds_alternative<std::shared_ptr<MarketResponse>>(res))
        {
            //TODO populate markets
            return std::get<std::shared_ptr<MarketResponse>>(res);
        }
        else
        {
            throw std::runtime_error(std::get<std::shared_ptr<ErrorResponse>>(res)->error->message->c_str());
        }

        //TODO return markets[marketTicker];
    }

    std::shared_ptr<MarketOrderbookResponse> Api::GetMarketOrderbook(std::string_view marketTicker)
    {
        OATPP_LOGD("Api", "GetMarketOrderbook");

        ApiResult<MarketOrderbookResponse> res = HandleResponse<MarketOrderbookResponse>(_api->GetMarketOrderbook(userAgent, basePath, login->token, std::string{marketTicker}, nullptr));

        if (std::holds_alternative<std::shared_ptr<MarketOrderbookResponse>>(res))
        {
            //TODO populate orderbooks
            return std::get<std::shared_ptr<MarketOrderbookResponse>>(res);
        }
        else
        {
            throw std::runtime_error(std::get<std::shared_ptr<ErrorResponse>>(res)->error->message->c_str());
        }

        //TODO return orderbooks[marketTicker];
    }

    std::shared_ptr<SeriesResponse> Api::GetSeries(std::string_view seriesTicker)
    {
        OATPP_LOGD("Api", "GetSeries");

        ApiResult<SeriesResponse> res = HandleResponse<SeriesResponse>(_api->GetSeries(userAgent, basePath, std::string{seriesTicker}));

        if (std::holds_alternative<std::shared_ptr<SeriesResponse>>(res))
        {
            //TODO populate series
            return std::get<std::shared_ptr<SeriesResponse>>(res);
        }
        else
        {
            throw std::runtime_error(std::get<std::shared_ptr<ErrorResponse>>(res)->error->message->c_str());
        }

        //TODO return series[seriesTicker];
    }

    std::shared_ptr<MarketCandlesticksResponse> Api::GetMarketCandlesticks(std::string_view seriesTicker, std::string_view marketTicker)
    {
        OATPP_LOGD("Api", "GetMarketCandlesticks");

        ApiResult<MarketCandlesticksResponse> res = HandleResponse<MarketCandlesticksResponse>(_api->GetMarketCandlesticks(userAgent, basePath, login->token, std::string{seriesTicker}, std::string{marketTicker}, nullptr, nullptr, nullptr));

        if (std::holds_alternative<std::shared_ptr<MarketCandlesticksResponse>>(res))
        {
            //TODO populate candlesticks
            return std::get<std::shared_ptr<MarketCandlesticksResponse>>(res);
        }
        else
        {
            throw std::runtime_error(std::get<std::shared_ptr<ErrorResponse>>(res)->error->message->c_str());
        }

        //return candlesticks[seriesTicker][marketTicker];
    }
}
