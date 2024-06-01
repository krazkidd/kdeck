#ifndef TYPES_H
#define TYPES_H

#include <string>
#include <string_view>

struct LoginRequest
{
    std::string_view email{};
    std::string_view password{};
};

struct LoginResponse
{
    std::string member_id{};
    std::string token{};
};

struct PortfolioBalanceResponse
{
    double balance{};
    //TODO try using std::optional and null coalescence
    double payout{};
};

#endif