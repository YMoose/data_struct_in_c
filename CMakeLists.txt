cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(MyStructInC LANGUAGES C)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(Unity REQUIRED)

message(STATUS "${Unity_INCLUDE_DIR}")

add_executable(
    test_tree 
    tree/test_tree.c
    mem.c
    ${Unity_SRC_DIR}/unity.c
    )

target_include_directories(
    test_tree
    PRIVATE
      ${Unity_SRC_DIR}
      ${CMAKE_CURRENT_SOURCE_DIR}
)

