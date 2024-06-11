project(kdeck)

add_executable(${PROJECT_NAME}
    main.cpp
)

target_include_directories(${PROJECT_NAME}
    PRIVATE ${CMAKE_SOURCE_DIR}/include
)

add_subdirectory(api)
add_subdirectory(ui)
add_subdirectory(util)

target_link_libraries(${PROJECT_NAME}
    PRIVATE api
    PRIVATE ui
    PRIVATE util
)