project(kdeck)

add_library(util
    event.cpp
)

target_include_directories(util
    PRIVATE ${CMAKE_SOURCE_DIR}/include
)