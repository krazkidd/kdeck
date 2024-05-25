#ifndef API_H
#define API_H

#include <string>

class Api
{
private:
    static std::string MakeRequest(std::string endpoint, std::string json);
public:
    // API requests
    static std::string RequestLoginToken(std::string email, std::string password);
};

#endif