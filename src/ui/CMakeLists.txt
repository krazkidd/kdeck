project(ui)

add_library(${PROJECT_NAME} STATIC
    App.cpp
    BalancePanel.cpp
    EventPositionPanel.cpp
    ExchangeAnnouncementsDialog.cpp
    ExchangeScheduleDialog.cpp
    ExchangeStatusDialog.cpp
    LoginDialog.cpp
    MainFrame.cpp
    MarketPositionPanel.cpp
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
        wxg
    PRIVATE
        OpenGL::EGL
        wx::core
        wx::base
        wx::gl
        oatpp::oatpp
)
