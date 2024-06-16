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

# see https://cmake.org/cmake/help/latest/module/FindwxWidgets.html
find_package(wxWidgets REQUIRED gl core base)
include(${wxWidgets_USE_FILE})

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        api
        #TODO requires cmake 3.27
        #wxWidgets::wxWidgets
        ${wxWidgets_LIBRARIES}
)
