project(api)

add_library(${PROJECT_NAME} STATIC
    Api.auth.cpp
    Api.portfolio.cpp
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        "${CMAKE_SOURCE_DIR}/include"
)

# see https://cmake.org/cmake/help/latest/module/FindBoost.html
find_package(Boost REQUIRED COMPONENTS json)
# see https://cmake.org/cmake/help/latest/module/FindCURL.html
find_package(CURL REQUIRED COMPONENTS HTTPS)

add_library(curlpp UNKNOWN IMPORTED)
set_target_properties(curlpp PROPERTIES
    IMPORTED_LOCATION "/usr/lib/x86_64-linux-gnu/libcurlpp.so.1"
    #INTERFACE_INCLUDE_DIRECTORIES "/usr/include/curlpp"
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    Boost::json
    CURL::libcurl
    curlpp
)

target_compile_options(${PROJECT_NAME} PUBLIC
    "-Wl,-z,relro"
    "-Wl,-z,now"
)
