cmake_minimum_required(VERSION 4.3)
project(Third C)

set(CMAKE_C_STANDARD 11)

add_executable(Third
        main.c
        methods.h)

target_link_libraries(Third PRIVATE m)