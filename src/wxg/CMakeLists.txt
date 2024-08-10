project(wxg)

add_library(${PROJECT_NAME} STATIC
    BaseExchangeAnnouncementsDialog.cpp
    BaseExchangeScheduleDialog.cpp
    BaseExchangeStatusDialog.cpp
    BaseLoginDialog.cpp
    BaseLogoutDialog.cpp
    BaseMainFrame.cpp
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        .
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
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
