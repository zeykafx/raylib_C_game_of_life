cmake_minimum_required(VERSION 3.16)
project(raylib_tests C)

set(CMAKE_C_STANDARD 99)

include_directories(include)
link_directories(lib)

add_executable(${PROJECT_NAME} sources/main.c sources/cell.c sources/cell.h sources/board.c sources/board.h sources/consts.h)

target_link_libraries(${PROJECT_NAME} raylib winmm.lib)