#include <string>
#include <string_view>
#include <stdexcept>

#include <boost/json.hpp>

#include "api/Api.h"

double Api::GetBalance()
{
    if (!IsLoggedIn())
    {
        throw std::logic_error("Not logged in.");
    }

    boost::json::value jsonRes = GetRequest("/portfolio/balance");

    if (auto jsonObj = jsonRes.if_object())
    {
        balance = jsonObj->at("balance").as_int64() / 100.0;
        //payout = jsonObj->at("payout").as_int64() / 100.0;
    }
    else
    {
        //TODO throw?
    }

    return balance;
}
