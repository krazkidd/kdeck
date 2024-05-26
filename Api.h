#ifndef API_H
#define API_H

#include <string>

#include <boost/json.hpp>

class Api
{
private:
    static inline std::string member_id;
    static inline std::string token;

    static boost::json::value MakeRequest(std::string_view endpoint, const boost::json::value &json);
public:
    // auth
    static void Login(std::string_view email, std::string_view password);
};

#endif