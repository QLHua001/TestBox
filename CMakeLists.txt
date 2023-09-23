cmake_minimum_required(VERSION 3.16.3)
project(TestBox VERSION 0.0.1)

set(CMAKE_BUILD_TYPE Debug)
set(EXECUTABLE_OUTPUT_PATH ../output)

add_executable(TestBox main.cpp)
