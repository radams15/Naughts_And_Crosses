cmake_minimum_required(VERSION 3.17)
project(Naughts_And_Crosses C)

set(CMAKE_C_STANDARD 99)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(Naughts_And_Crosses main.c)

target_link_libraries(Naughts_And_Crosses ${CURSES_LIBRARIES})