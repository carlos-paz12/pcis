cmake_minimum_required(VERSION 3.10)
project(instruction_set_simulator)

set(CMAKE_CXX_STANDARD 11)

include_directories(inc)

set( APP_NAME "pcis" )
add_executable(${APP_NAME} src/main/main.cpp src/cesar.cpp src/neander.cpp src/ramses.cpp src/memory.cpp src/main/utils.cpp)