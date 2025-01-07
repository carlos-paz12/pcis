cmake_minimum_required(VERSION 3.10)
project(instruction_set_simulator)

set(CMAKE_CXX_STANDARD 11)

include_directories(inc)

add_executable(instruction-set-simulator src/main/main.cpp src/cesar.cpp src/neander.cpp src/ramses.cpp src/memory.cpp src/Utils.cpp)