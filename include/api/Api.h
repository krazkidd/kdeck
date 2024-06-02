#ifndef API_H
#define API_H

#include <string>
#include <utility>
#include <vector>

#include <boost/json.hpp>

#include "api/types.h"

//constexpr std::string_view kKalshiApiUrl{"https://trading-api.kalshi.com/trade-api/v2"};
constexpr std::string_view kKalshiApiUrl{"https://demo-api.kalshi.co/trade-api/v2"};

class Api
{
public:
    // auth
    static void Login(std::string_view email, std::string_view password);
    static void Logout();

    // portfolio
    static double GetBalance();
    static std::vector<PortfolioPositionsResponse::MarketPosition> GetPositions();

    // helpers
    static bool IsLoggedIn();

private:
    // auth
    static inline LoginResponse login;

    // portfolio
    static inline PortfolioBalanceResponse balance;
    static inline PortfolioPositionsResponse positions;

    // core
    static boost::json::value MakeRequest(std::string_view endpoint, bool doPostMethod = false);
    static boost::json::value MakeRequest(std::string_view endpoint, const boost::json::value &json, bool doPostMethod = false);

    static void GetRequest(std::string_view endpoint)
    {
        MakeRequest(endpoint);
    }

    template <typename TResponse>
    static TResponse GetRequest(std::string_view endpoint)
    {
        return boost::json::value_to<TResponse>(MakeRequest(endpoint));
    }

    template <typename TResponse, typename TRequest>
    static TResponse GetRequest(std::string_view endpoint, TRequest&& req)
    {
        boost::json::value jv;
        boost::json::value_from<TRequest>(std::forward<TRequest>(req), jv);

        return boost::json::value_to<TResponse>(MakeRequest(endpoint, jv));
    }

    static void PostRequest(std::string_view endpoint)
    {
        MakeRequest(endpoint, true);
    }

    template <typename TResponse>
    static TResponse PostRequest(std::string_view endpoint)
    {
        return boost::json::value_to<TResponse>(MakeRequest(endpoint, true));
    }

    template <typename TResponse, typename TRequest>
    static TResponse PostRequest(std::string_view endpoint, TRequest&& req)
    {
        boost::json::value jv;
        boost::json::value_from<TRequest>(std::forward<TRequest>(req), jv);

        return boost::json::value_to<TResponse>(MakeRequest(endpoint, jv, true));
    }
};

#endif