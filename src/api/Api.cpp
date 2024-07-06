#include <string_view>
#include <stdexcept>
#include <variant>

#include "oatpp/core/Types.hpp"
#include "oatpp/network/tcp/client/ConnectionProvider.hpp"
#include "oatpp/network/Url.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/web/client/HttpRequestExecutor.hpp"
#include "oatpp/web/protocol/http/incoming/Response.hpp"
#include "oatpp-openssl/Config.hpp"
#include "oatpp-openssl/client/ConnectionProvider.hpp"
#include "oatpp-openssl/configurer/TrustStore.hpp"

#include "api/Api.hpp"
#include "api/types.hpp"

namespace kdeck
{

    // constructor ////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////

    Api::Api(std::string_view apiEndpointUrl, std::string_view sslTrustStoreDir)
        : login{nullptr}
    {
        auto url = oatpp::network::Url::Parser::parseUrl(std::string{apiEndpointUrl});

        std::shared_ptr<oatpp::network::ClientConnectionProvider> connectionProvider = nullptr;

        if (url.scheme.equalsCI_ASCII("https"))
        {
            auto config = oatpp::openssl::Config::createDefaultClientConfigShared();

            if (!sslTrustStoreDir.empty())
            {
                //TODO this throws an error
                config->addContextConfigurer(std::make_shared<oatpp::openssl::configurer::TrustStore>(std::string{sslTrustStoreDir}, nullptr));
            }

            connectionProvider = oatpp::openssl::client::ConnectionProvider::createShared(config, {url.authority.host, static_cast<uint16_t>(url.authority.port == -1 ? 443 : url.authority.port)});
        }
        else if (url.scheme.equalsCI_ASCII("http"))
        {
            connectionProvider = oatpp::network::tcp::client::ConnectionProvider::createShared({url.authority.host, static_cast<uint16_t>(url.authority.port == -1 ? 80 : url.authority.port)});
        }
        else
        {
            //TODO
            //throw std::runtime_error("Unsupported scheme: " + *url.scheme);
        }

        auto requestExecutor = oatpp::web::client::HttpRequestExecutor::createShared(connectionProvider);

        // auto serializeConfig = oatpp::parser::json::mapping::Serializer::Config::createShared();
        // serializeConfig->useBeautifier = true;

        // auto deserializeConfig = oatpp::parser::json::mapping::Deserializer::Config::createShared();

        objectMapper = oatpp::parser::json::mapping::ObjectMapper::createShared(/* serializeConfig, deserializeConfig */);
        _api = _Api::createShared(requestExecutor, objectMapper);
    }

}
