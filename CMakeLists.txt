cmake_minimum_required(VERSION 3.28)
project(pcis VERSION 1.0.0 LANGUAGES CXX )

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

set ( TEST_DRIVER "pcis")
add_subdirectory(tests)    # This will ask the tests to be generated