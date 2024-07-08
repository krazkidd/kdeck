#include <memory>
#include <sstream>
#include <string>
#include <string_view>
#include <utility>
#include <variant>

#include "oatpp/core/Types.hpp"
#include "oatpp/web/protocol/http/incoming/Response.hpp"

#include "api/types.hpp"

namespace kdeck
{
    template <typename TResponse>
    ApiResult<TResponse> Api::HandleResponse(std::shared_ptr<oatpp::web::protocol::http::incoming::Response> response)
    {
        OATPP_LOGD("Api", "Response => %d %s", response->getStatusCode(), response->getStatusDescription()->c_str());

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
                auto errorResponse = response->readBodyToDto<oatpp::Object<ErrorResponse>>(objectMapper.get());

                if (errorResponse->error->message)
                {
                    OATPP_LOGE("Api", "Error => %s", errorResponse->error->message->c_str());
                }

                return errorResponse.getPtr();
        }

        throw std::runtime_error("Unknown JSON error.");
    }
}
