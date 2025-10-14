cmake_minimum_required(VERSION 3.10)
project(STLContainers)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(app src/main.cpp)
add_executable(test test.cpp)
