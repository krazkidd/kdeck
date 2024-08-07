#include <string>
#include <string_view>

#include <wx/string.h>

#include "oatpp/core/async/Coroutine.hpp"
#include "oatpp/core/data/stream/FileStream.hpp"
#include "oatpp/core/Types.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"

#include "app_config.hpp"
#include "config/Config.hpp"

namespace kdeck
{
    // constructor ////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////

    Config::Config()
        : m_objectMapper{oatpp::parser::json::mapping::ObjectMapper::createShared(
            oatpp::parser::json::mapping::Serializer::Config::createShared(),
            oatpp::parser::json::mapping::Deserializer::Config::createShared()
          )},
          m_defaultConfig{MakeDefaultConfig()}
    {
        std::string xdgConfigHome = std::getenv("XDG_CONFIG_HOME") ? std::getenv("XDG_CONFIG_HOME") : "";

        if (!xdgConfigHome.empty())
        {
            m_filePath = wxString::Format("%s/%s/%s", xdgConfigHome, kProjectName, kConfigFilename);
        }
        else
        {
            std::string home = std::getenv("HOME") ? std::getenv("HOME") : "";

            if (!home.empty())
            {
                //TODO prefer .config/ directory if it exists

                m_filePath = wxString::Format("%s/%s/%s", home, kProjectName, kConfigFilename);
            }
            else
            {
                m_filePath = wxString::Format("%s/%s", kProjectName, kConfigFilename);
            }
        }

        auto serializeConfig = m_objectMapper->getSerializer()->getConfig();
        serializeConfig->useBeautifier = true;
        // we will use default values if not set in user config
        //serializeConfig->includeNullFields = true;
        // this is not a burden we should put on the user
        //serializeConfig->alwaysIncludeRequired = true;

        auto deserializeConfig = m_objectMapper->getDeserializer()->getConfig();
        deserializeConfig->allowUnknownFields = true;

        try
        {
            Load();
        }
        catch (const std::exception &e)
        {
            //TODO ideally, we would want to notify the user about a config file error;
            //     in which case, we probably don't want to perform the Load() operation
            //     in the constructor

            m_activeConfig = MakeDefaultConfig();
        }
    }

    void Config::Save()
    {
        //TODO i think m_activeConfig should never be null, but if it is, we should save the default config
        if (!m_activeConfig)
        {
            throw std::runtime_error("User config is not loaded.");
        }

        //TODO we need to create any missing directories in the path

        auto fileStream = oatpp::data::stream::FileOutputStream(m_filePath.c_str());
        fileStream.setOutputStreamIOMode(oatpp::data::stream::BLOCKING);

        if (!fileStream.getFile())
        {
            throw new std::runtime_error("Failed to open the config file for writing.");
        }

        oatpp::String json = m_objectMapper->writeToString(oatpp::Void(m_activeConfig));

        static auto action = oatpp::async::Action::createActionByType(oatpp::async::Action::TYPE_NONE);

        if (fileStream.write(json->data(), json->size(), action) != json->size())
        {
            throw new std::runtime_error("Failed to write the config file.");
        }
    }

    void Config::Load()
    {
        //TODO what is best practice for buffer size?
        static constexpr int32_t bufferSize = 1024 * 1024;

        auto fileStream = oatpp::data::stream::FileInputStream(m_filePath.c_str());
        fileStream.setInputStreamIOMode(oatpp::data::stream::BLOCKING);

        if (!fileStream.getFile())
        {
            throw new std::runtime_error("Failed to open the config file for reading.");
        }

        auto json = std::make_shared<char*>(new char[bufferSize]);

        static auto action = oatpp::async::Action::createActionByType(oatpp::async::Action::TYPE_NONE);

        if (fileStream.read(*json, bufferSize, action) == 0)
        {
            throw new std::runtime_error("Failed to read the config file.");
        }

        m_activeConfig = m_objectMapper->readFromString<oatpp::Object<UserConfig>>(std::string{*json}).getPtr();

        //TODO validate the config?
        //TODO check the version?
        //TODO check if the fields are empty? use default values?
    }

    std::string Config::GetKalshiApiUrl() const
    {
        return m_activeConfig->KalshiApiUrl ? m_activeConfig->KalshiApiUrl->c_str() : m_defaultConfig->KalshiApiUrl->c_str();
    }

    std::string Config::GetSslTrustStoreDir() const
    {
        return m_activeConfig->SslTrustStoreDir ? m_activeConfig->SslTrustStoreDir->c_str() : m_defaultConfig->SslTrustStoreDir->c_str();
    }

    std::string Config::GetEmail() const
    {
        return m_activeConfig->Email ? m_activeConfig->Email->c_str() : m_defaultConfig->Email->c_str();
    }

    bool Config::GetShowClosedPositions() const
    {
        return m_activeConfig->ShowClosedPositions ? m_activeConfig->ShowClosedPositions : m_defaultConfig->ShowClosedPositions;
    }

    void Config::SetEmail(std::string email)
    {
        m_activeConfig->Email = oatpp::String{email};
    }

    void Config::SetShowClosedPositions(bool doShow)
    {
        m_activeConfig->ShowClosedPositions = doShow;
    }

    std::shared_ptr<Config::UserConfig> Config::MakeDefaultConfig()
    {
        auto config = UserConfig::createShared();

        config->Version = kConfigVersion;
        config->KalshiApiUrl = std::string{kKalshiApiUrl};
        config->SslTrustStoreDir = std::string{kSslTrustStoreDir};
        config->Email = std::string{};
        config->ShowClosedPositions = false;

        return config.getPtr();
    }

}
