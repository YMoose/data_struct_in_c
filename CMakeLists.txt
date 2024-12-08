cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(MyStructInC LANGUAGES C)

list(APPEND CMAKE_MODULE_PATH 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake
)

find_package(Unity REQUIRED)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    message(STATUS "Configuring on/for Linux")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    message(STATUS "Configuring on/for Windows")
else()
    message(STATUS "Configuring on/for ${CMAKE_SYSTEM_NAME}")
endif()


#message(STATUS "unity is ${Unity_SRC_DIR}")


macro(add_unit_test _name)
    add_executable(
        ${_name} 
        src/test/${_name}.c
        ${Unity_SRC_FILE}
        )
    target_include_directories(
        ${_name}
        PRIVATE
            ${Unity_SRC_DIR}
            ${CMAKE_CURRENT_SOURCE_DIR}
            ${CMAKE_CURRENT_SOURCE_DIR}/src
    )
    add_test(
        NAME
            ${_name}
        COMMAND
            $<TARGET_FILE:${_name}>
        )    
endmacro()

enable_testing()

# add_unit_test(test_tree src/test/test_tree.c)
add_unit_test(test_list src/test/test_list.c)
add_unit_test(test_queue src/test/test_queue.c)




