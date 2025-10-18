cmake_minimum_required(VERSION 3.10)
project(STLContainers)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# include dir
include_directories(include)

# main app
add_executable(app src/main.cpp)
target_include_directories(app PRIVATE include)

# GoogleTest via FetchContent
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
# For Windows: prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# tests executable
add_executable(tests tests/test.cpp)
target_include_directories(tests PRIVATE include)
target_link_libraries(tests PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(tests)
