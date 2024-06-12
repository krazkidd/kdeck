project(kdeck)

add_executable(${PROJECT_NAME}
    main.cpp
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        "${CMAKE_SOURCE_DIR}/include"
)

# see https://cmake.org/cmake/help/latest/module/FindwxWidgets.html
find_package(wxWidgets REQUIRED gl core base)
include(${wxWidgets_USE_FILE})

#TODO requires cmake 3.27
# target_link_libraries(${PROJECT_NAME}
#    PUBLIC
#         wxWidgets::wxWidgets
# )
target_link_libraries(${PROJECT_NAME}
    PUBLIC
        ui
        ${wxWidgets_LIBRARIES}
)

add_subdirectory(api)
add_subdirectory(ui)
