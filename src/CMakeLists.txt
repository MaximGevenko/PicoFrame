add_subdirectory(HAL)
add_subdirectory(application)
add_subdirectory(utils)
add_subdirectory(middleware)

target_include_directories(led-matrix PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
)
