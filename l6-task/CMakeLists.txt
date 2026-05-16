cmake_minimum_required(VERSION 3.20.0)

list(APPEND BOARD_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND DTS_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

find_package(Zephyr REQUIRED)
project(l4-task1)

target_sources(app PRIVATE src/main.c)
target_sources(app PRIVATE driver/my_driver.c)
add_subdirectory(driver)
