project(kdeck)

add_library(ui
    App.cpp
    BalancePanel.cpp
    EventPositionPanel.cpp
    LoginPanel.cpp
    MainFrame.cpp
    MarketPositionPanel.cpp
    PortfolioPanel.cpp
    StaticCurrency.cpp
)

target_include_directories(ui
    PRIVATE ${CMAKE_SOURCE_DIR}/include
)