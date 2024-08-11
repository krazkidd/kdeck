project(wxfb)

add_library(${PROJECT_NAME} STATIC
    App.cpp
    PortfolioPanel.cpp
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src/wxfb>
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        ui
    PRIVATE
        OpenGL::EGL
        wx::core
        wx::base
        wx::gl
)
