project(api)

add_library(${PROJECT_NAME} STATIC
    Api.cpp
    Api.auth.cpp
    Api.exchange.cpp
    Api.portfolio.cpp
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Boost::boost
        Boost::json
        CURL::libcurl
        unofficial::curlpp::curlpp
        oatpp::oatpp
        oatpp::oatpp-openssl
)

target_compile_options(${PROJECT_NAME}
    PUBLIC
        "-Wl,-z,relro"
        "-Wl,-z,now"
)
