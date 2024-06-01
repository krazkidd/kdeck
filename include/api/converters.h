#ifndef CONVERTERS_H
#define CONVERTERS_H

#include <boost/json.hpp>

#include "api/types.h"

inline void tag_invoke(const boost::json::value_from_tag &TODO, boost::json::value &jv, const LoginRequest &req)
{
    jv = {
        { "email", req.email },
        { "password", req.password }
    };
}

inline LoginResponse tag_invoke(const boost::json::value_to_tag<LoginResponse> &TODO, const boost::json::value &jv)
{
    if (auto jo = jv.if_object())
    {
        return LoginResponse{
            jo->at("member_id").as_string().c_str(),
            jo->at("token").as_string().c_str()
        };
    }
    else
    {
        throw std::runtime_error("Invalid JSON response.");
    }
}

#endif