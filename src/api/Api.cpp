#include <string_view>

#include "oatpp/network/tcp/client/ConnectionProvider.hpp"
#include "oatpp/network/Url.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/web/client/HttpRequestExecutor.hpp"
#include "oatpp-openssl/Config.hpp"
#include "oatpp-openssl/client/ConnectionProvider.hpp"
#include "oatpp-openssl/configurer/TrustStore.hpp"

#include "api/Api.hpp"

namespace kdeck
{

    // constructor ////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////

    Api::Api(std::string_view apiEndpointUrl, std::string_view sslTrustStoreDir)
        : login{nullptr}
    {
        auto url = oatpp::network::Url::Parser::parseUrl(std::string{apiEndpointUrl});

        // remove leading slash because oatpp's API_CALL() macro preserves it somehow
        basePath = url.path->substr(url.path->at(0) == '/' ? 1 : 0);

        std::shared_ptr<oatpp::network::ClientConnectionProvider> connectionProvider = nullptr;

        if (url.scheme.equalsCI_ASCII("https"))
        {
            auto config = oatpp::openssl::Config::createDefaultClientConfigShared();

            if (!sslTrustStoreDir.empty())
            {
                config->addContextConfigurer(std::make_shared<oatpp::openssl::configurer::TrustStore>(nullptr, std::string{sslTrustStoreDir}));
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

        objectMapper = oatpp::parser::json::mapping::ObjectMapper::createShared();
        _api = _Api::createShared(requestExecutor, objectMapper);
    }

}
