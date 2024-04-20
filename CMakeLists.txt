cmake_minimum_required(VERSION 3.26)
project(op_lab_17 C)

set(CMAKE_C_STANDARD 11)

add_executable(op_lab_17 main.c
        libs/data_struct/string/string.c
        libs/data_struct/string/string.h)

add_subdirectory(libs)

target_link_libraries(data_struct)