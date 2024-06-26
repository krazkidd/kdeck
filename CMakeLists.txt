cmake_minimum_required(VERSION 3.0.0)
project(kdeck VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(OSBitness 32)
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(OSBitness 64)
endif()

set(FullOutputDir "${CMAKE_BINARY_DIR}/bin/${CMAKE_SYSTEM_NAME}${OSBitness}/${CMAKE_BUILD_TYPE}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${FullOutputDir}/static_libs")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${FullOutputDir}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${FullOutputDir}")

#TODO it is recommended to use CI tools to enforce warnings limits
# target_compile_options(${PROJECT_NAME}
#     PUBLIC
#         "-Wall"
#         "-Werror"
#         "-fdiagnostics-color=always"
# )

configure_file(
    "${CMAKE_SOURCE_DIR}/include/config.hpp.in"
    "${CMAKE_BINARY_DIR}/include/config.hpp"
)

#TODO GitHub Copilot suggested this to combine source and generated headers
# install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
# install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

add_subdirectory(src)
