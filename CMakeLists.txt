cmake_minimum_required(VERSION 3.20)

project(compiledb4ms)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()
find_package(GTest CONFIG REQUIRED)
include(GoogleTest)

add_executable(acceptance_test
  tests/usage.cpp
)
target_link_libraries(acceptance_test
  PRIVATE GTest::gtest_main
)
gtest_discover_tests(acceptance_test)
