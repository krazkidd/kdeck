cmake_minimum_required(VERSION 3.20.0)
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

find_package(OpenGL REQUIRED)
find_package(wxWidgets CONFIG REQUIRED COMPONENTS core base gl)

find_package(Boost REQUIRED COMPONENTS format json)
find_package(CURL REQUIRED)
find_package(unofficial-curlpp CONFIG REQUIRED)
find_package(oatpp CONFIG REQUIRED)
find_package(oatpp-openssl CONFIG REQUIRED)

# Check if the build type is Debug
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    # do nothing
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_definitions(OATPP_DISABLE_LOGV)
    add_compile_definitions(OATPP_DISABLE_LOGD)
    #add_compile_definitions(OATPP_DISABLE_LOGI)
    #add_compile_definitions(OATPP_DISABLE_LOGW)
    #add_compile_definitions(OATPP_DISABLE_LOGE)
else()
    # do nothing
endif()

add_subdirectory(src)
