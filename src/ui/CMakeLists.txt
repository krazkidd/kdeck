project(ui)

add_library(${PROJECT_NAME} STATIC
    App.cpp
    ExchangeAnnouncementsDialog.cpp
    ExchangeScheduleDialog.cpp
    ExchangeStatusDialog.cpp
    LoginDialog.cpp
    MainFrame.cpp
    PortfolioPanel.cpp
    StaticCurrency.cpp
    event.cpp
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        api
        config
        wxfb
    PRIVATE
        OpenGL::EGL
        wx::core
        wx::base
        wx::gl
        oatpp::oatpp
)
