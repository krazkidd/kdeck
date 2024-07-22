#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <memory>
#include <string>
#include <string_view>

#include "oatpp/core/Types.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/core/macro/codegen.hpp"

namespace kdeck
{
    class Config
    {
        #include OATPP_CODEGEN_BEGIN(DTO)

        class UserConfig
            : public oatpp::DTO
        {

            DTO_INIT(UserConfig, DTO)

            DTO_FIELD(Int32, Version);
            DTO_FIELD(String, KalshiApiUrl);
            DTO_FIELD(String, SslTrustStoreDir);
            DTO_FIELD(String, Email);
            DTO_FIELD(Boolean, ShowClosedPositions);

        };

        #include OATPP_CODEGEN_END(DTO)

    public:
        Config();

        void Save();

        void Load();

        std::string GetKalshiApiUrl() const;

        std::string GetSslTrustStoreDir() const;

        std::string GetEmail() const;

        bool GetShowClosedPositions() const;

        void SetEmail(std::string email);

        void SetShowClosedPositions(bool doShow);

    private:
        static constexpr int32_t kConfigVersion = 1;
        static constexpr std::string_view kConfigFilename = "config.json";

        const std::shared_ptr<UserConfig> m_defaultConfig;

        std::string m_filePath;

        std::shared_ptr<oatpp::parser::json::mapping::ObjectMapper> m_objectMapper;
        std::shared_ptr<UserConfig> m_activeConfig;

        static std::shared_ptr<UserConfig> MakeDefaultConfig();
    };
}

#endif
