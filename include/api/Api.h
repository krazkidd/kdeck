#ifndef API_H
#define API_H

#include <string>

#include <boost/json.hpp>

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

    // helpers
    static bool IsLoggedIn();

private:
    // auth
    static inline std::string member_id;
    static inline std::string token;

    // portfolio
    static inline double balance;
    //static inline double payout;

    // core
    static boost::json::value MakeRequest(std::string_view endpoint, bool doPostMethod = false);
    static boost::json::value MakeRequest(std::string_view endpoint, const boost::json::value &json, bool doPostMethod = false);

    static boost::json::value GetRequest(std::string_view endpoint);
    static boost::json::value GetRequest(std::string_view endpoint, const boost::json::value &json);

    static boost::json::value PostRequest(std::string_view endpoint);
    static boost::json::value PostRequest(std::string_view endpoint, const boost::json::value &json);
};

#endif