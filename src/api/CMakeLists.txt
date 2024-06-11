project(kdeck)

add_library(api
    Api.auth.cpp
    Api.core.cpp
    Api.helpers.cpp
    Api.portfolio.cpp
)

target_include_directories(api
    PRIVATE ${CMAKE_SOURCE_DIR}/include
)