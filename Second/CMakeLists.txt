cmake_minimum_required(VERSION 4.3)
project(Second C)

set(CMAKE_C_STANDARD 11)

add_executable(Second
        matrix_processing.c)

target_link_libraries(Second PRIVATE m)