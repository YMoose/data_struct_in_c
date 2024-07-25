cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(MyStructInC LANGUAGES C)

list(APPEND CMAKE_MODULE_PATH 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake
)

find_package(Unity REQUIRED)
find_package(MyStructInC REQUIRED)

execute_process(
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/scripts/gen_header_file.sh ${CMAKE_CURRENT_SOURCE_DIR}/src
)

message(STATUS "unity is ${Unity_SRC_DIR}")

add_executable(
    test_tree 
    src/tree/test_tree.c
    src/mem.c
    ${Unity_SRC_FILE}
    )

target_include_directories(
    test_tree
    PRIVATE
      ${Unity_SRC_DIR}
      ${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(MyStructInC
  STATIC
  src/mem.c
)

enable_testing()



