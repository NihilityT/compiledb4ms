cmake_minimum_required(VERSION 3.20)

project(compiledb4ms)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_compile_options(
  "$<$<CXX_COMPILER_ID:MSVC>:/W4;/WX>"
  "$<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall;-Wextra;-Wpedantic;-Werror>"
)

enable_testing()
find_package(GTest CONFIG REQUIRED)
include(GoogleTest)

add_library(libutils STATIC
  libutils/utils.h
  libutils/utils.cpp
)
target_include_directories(libutils
  PUBLIC ${CMAKE_SOURCE_DIR}
)

include(GoogleTest)

add_executable(libutils_test
  libutils/utils.test.cpp
)
target_link_libraries(libutils_test
  PRIVATE GTest::gtest_main
  PRIVATE libutils
)
gtest_discover_tests(libutils_test
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)


add_executable(compiledb4ms
  compiledb4ms/command_object.h
  compiledb4ms/command_object.cpp
  compiledb4ms/main.cpp
)
target_include_directories(compiledb4ms
  PRIVATE ${CMAKE_SOURCE_DIR}
)

add_executable(compiledb4ms_test
  compiledb4ms/command_object.h
  compiledb4ms/command_object.cpp
  compiledb4ms/command_object.test.cpp
)
target_include_directories(compiledb4ms_test
  PRIVATE ${CMAKE_SOURCE_DIR}
)
target_link_libraries(compiledb4ms_test
  GTest::gtest_main
)
gtest_discover_tests(compiledb4ms_test)

add_executable(acceptance_test
  tests/usage.cpp
)
target_link_libraries(acceptance_test
  PRIVATE GTest::gtest_main
  PRIVATE libutils
)
gtest_discover_tests(acceptance_test
  PROPERTIES ENVIRONMENT compiledb4ms=$<TARGET_FILE:compiledb4ms>
)
