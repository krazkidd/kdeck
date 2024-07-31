#include <memory>

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
                oatpp::String contentType = response->getHeaders().get("Content-Type");

                // the MIME type could contain parameters (e.g. "application/json; charset=utf-8")
                if (contentType->find("application/json") != std::string::npos)
                {
                    auto errorResponse = response->readBodyToDto<oatpp::Object<ErrorResponse>>(objectMapper.get());

                    if (errorResponse->error->message)
                    {
                        OATPP_LOGE("Api", "Error => %s", errorResponse->error->message->c_str());
                    }

                    return errorResponse.getPtr();
                }
                else
                {
                    // NOTE: It appears the API may be behind a Web Application Firewall (WAF)
                    //       and in some cases is rejecting requests with an HTML response. We
                    //       consider this a hard error and throw, since it violates the spec.
                    //       Source: https://github.com/krazkidd/kdeck/issues/69

                    oatpp::String errorBody = response->readBodyToString();

                    OATPP_LOGE("Api", "Error => (%s)\n%s", contentType->c_str(), errorBody->c_str());

                    throw std::runtime_error("Unknown API error.");
                }
        }

        throw std::runtime_error("Unknown API error.");
    }
}
