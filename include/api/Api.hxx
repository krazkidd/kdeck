#include <memory>
#include <sstream>
#include <string>
#include <string_view>
#include <utility>
#include <variant>

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>
#include <curlpp/Infos.hpp>
#include <boost/json.hpp>

#include "oatpp/core/Types.hpp"
#include "oatpp/web/protocol/http/incoming/Response.hpp"

#include "api/types.hpp"

namespace kdeck
{
    template <typename TResponse>
    ApiResult<TResponse> Api::HandleResponse(std::shared_ptr<oatpp::web::protocol::http::incoming::Response> response)
    {
        switch (response->getStatusCode())
        {
            // success
            case 200:
            case 201:
                return response->readBodyToDto<oatpp::Object<TResponse>>(objectMapper.get()).getPtr();

            // success (no response body)
            case 204:
                // NOTE: If we try to parse an empty body (not valid JSON),
                //       oatpp will throw. So we just return
                //       the expected type (should be VoidResponse).

                //return response->readBodyToDto<oatpp::Object<TResponse>>(objectMapper.get()).getPtr();
                return std::make_shared<TResponse>(TResponse{});

            // error
            case 400:
            case 401:
            case 403:
            case 404:
            case 500:
            case 503:
                return response->readBodyToDto<oatpp::Object<ErrorResponse>>(objectMapper.get()).getPtr();
        }

        throw std::runtime_error("Unknown JSON error.");
    }
}
