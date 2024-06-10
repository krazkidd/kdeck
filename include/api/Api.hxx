#include <string_view>
#include <utility>

#include <boost/json.hpp>

template <typename TResponse>
TResponse Api::GetRequest(std::string_view endpoint)
{
    return boost::json::value_to<TResponse>(MakeRequest(endpoint));
}

template <typename TResponse, typename TRequest>
TResponse Api::GetRequest(std::string_view endpoint, TRequest&& req)
{
    boost::json::value jv;
    boost::json::value_from<TRequest>(std::forward<TRequest>(req), jv);

    return boost::json::value_to<TResponse>(MakeRequest(endpoint, jv));
}

template <typename TResponse>
TResponse Api::PostRequest(std::string_view endpoint)
{
    return boost::json::value_to<TResponse>(MakeRequest(endpoint, true));
}

template <typename TResponse, typename TRequest>
TResponse Api::PostRequest(std::string_view endpoint, TRequest&& req)
{
    boost::json::value jv;
    boost::json::value_from<TRequest>(std::forward<TRequest>(req), jv);

    return boost::json::value_to<TResponse>(MakeRequest(endpoint, jv, true));
}
