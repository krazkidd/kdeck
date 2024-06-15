#ifndef API_HPP
#define API_HPP

#include <string_view>
#include <vector>

#include <boost/json.hpp>

#include "api/types.hpp"

//constexpr std::string_view kKalshiApiUrl{"https://trading-api.kalshi.com/trade-api/v2"};
constexpr std::string_view kKalshiApiUrl{"https://demo-api.kalshi.co/trade-api/v2"};

template <typename TResponse>
using ApiResult = std::variant<TResponse, ErrorResponse>;

class Api
{
public:
    // auth
    static void Login(std::string_view email, std::string_view password);
    static void Logout();

    // exchange
    static ExchangeAnnouncementsResponse GetExchangeAnnouncements();
    static ExchangeScheduleResponse GetExchangeSchedule();
    static ExchangeStatusResponse GetExchangeStatus();

    // portfolio
    static double GetBalance();
    static PortfolioPositionsResponse GetPositions();

    // helpers
    static bool IsLoggedIn();

    static std::vector<PortfolioPositionsResponse::EventPosition> GetEventPositions();
    static std::vector<PortfolioPositionsResponse::MarketPosition> GetMarketPositions();

private:
    // auth
    static inline LoginResponse login;

    // exchange
    static inline ExchangeAnnouncementsResponse announcements;
    static inline ExchangeScheduleResponse schedule;
    static inline ExchangeStatusResponse status;

    // portfolio
    static inline PortfolioBalanceResponse balance;
    static inline PortfolioPositionsResponse positions;

    // core
    template <typename TResponse>
    static ApiResult<TResponse> HandleResponse(int responseCode, const std::stringstream &responseBody);

    template <typename TResponse>
    static ApiResult<TResponse> MakeRequest(std::string_view endpoint, bool doPostMethod = false);

    template <typename TResponse>
    static ApiResult<TResponse> MakeRequest(std::string_view endpoint, const boost::json::value &json, bool doPostMethod = false);

    template <typename TResponse>
    static ApiResult<TResponse> GetRequest(std::string_view endpoint);

    template <typename TResponse, typename TRequest>
    static ApiResult<TResponse> GetRequest(std::string_view endpoint, TRequest&& req);

    template <typename TResponse>
    static ApiResult<TResponse> PostRequest(std::string_view endpoint);

    template <typename TResponse, typename TRequest>
    static ApiResult<TResponse> PostRequest(std::string_view endpoint, TRequest&& req);
};

#include "api/Api.hxx"

#endif