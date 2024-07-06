#include <chrono>

#include <boost/json.hpp>

#include "api/types.hpp"

namespace kdeck
{
    // we don't use this but it's required to compile
    inline VoidResponse tag_invoke(const boost::json::value_to_tag<VoidResponse> &, const boost::json::value &jv)
    {
        return VoidResponse{};
    }

    inline ErrorResponse tag_invoke(const boost::json::value_to_tag<ErrorResponse> &, const boost::json::value &jv)
    {
        return ErrorResponse{
            jv.at("code").as_string().c_str(),
            //TODO try using std::optional
            //jo->at("details").as_string().c_str(),
            jv.at("message").as_string().c_str()
        };
    }
}
