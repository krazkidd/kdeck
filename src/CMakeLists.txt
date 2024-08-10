project(kdeck)

add_executable(${PROJECT_NAME}
    main.cpp
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
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

add_subdirectory(api)
add_subdirectory(config)
add_subdirectory(ui)
add_subdirectory(wxfb)
