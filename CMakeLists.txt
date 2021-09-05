cmake_minimum_required(VERSION 3.14)

set(CMAKE_C_STANDARD 90)

project(miniLaska)

file(GLOB_RECURSE TARGET_SOURCES ${CMAKE_CURRENT_LIST_DIR}/src/*.c)

add_executable(miniLaska ${TARGET_SOURCES})

install(TARGETS miniLaska)

enable_testing()
add_test(NAME miniLaska COMMAND miniLaska)
