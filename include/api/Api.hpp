#ifndef API_HPP
#define API_HPP

#include <map>
#include <string_view>
#include <vector>

#include <boost/json.hpp>

#include "config.hpp"
#include "api/types.hpp"

template <typename TResponse>
using ApiResult = std::variant<TResponse, ErrorResponse>;

class Api
{
public:
    // auth
    void Login(std::string_view email, std::string_view password);
    void Logout();

    // exchange
    ExchangeAnnouncementsResponse GetExchangeAnnouncements();
    ExchangeScheduleResponse GetExchangeSchedule();
    ExchangeStatusResponse GetExchangeStatus();

    // portfolio
    double GetBalance();
    PortfolioPositionsResponse GetPositions();

    // helpers
    bool IsLoggedIn();

    std::vector<PortfolioPositionsResponse::EventPosition> GetEventPositions();
    std::vector<PortfolioPositionsResponse::MarketPosition> GetMarketPositions(std::string_view eventTicker = "");

private:
    // auth
    LoginResponse login;

    // exchange
    ExchangeAnnouncementsResponse announcements;
    ExchangeScheduleResponse schedule;
    ExchangeStatusResponse status;

    // portfolio
    PortfolioBalanceResponse balance;
    PortfolioPositionsResponse positions;

    std::map<std::string, PortfolioPositionsResponse::EventPosition> eventsMap;
    std::map<std::string, std::map<std::string, PortfolioPositionsResponse::MarketPosition>> marketsMap;

    // core
    template <typename TResponse>
    ApiResult<TResponse> HandleResponse(int responseCode, const std::stringstream &responseBody);

    template <typename TResponse>
    ApiResult<TResponse> MakeRequest(std::string_view endpoint, bool doPostMethod = false);

    template <typename TResponse>
    ApiResult<TResponse> MakeRequest(std::string_view endpoint, const boost::json::value &json, bool doPostMethod = false);

    template <typename TResponse>
    ApiResult<TResponse> GetRequest(std::string_view endpoint);

    template <typename TResponse, typename TRequest>
    ApiResult<TResponse> GetRequest(std::string_view endpoint, TRequest&& req);

    template <typename TResponse>
    ApiResult<TResponse> PostRequest(std::string_view endpoint);

    template <typename TResponse, typename TRequest>
    ApiResult<TResponse> PostRequest(std::string_view endpoint, TRequest&& req);
};

#include "api/Api.hxx"

#endif
