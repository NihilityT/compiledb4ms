add_executable(compiledb4ms
  command_object.h
  command_object.cpp
  main.cpp
)
target_include_directories(compiledb4ms
  PRIVATE ${CMAKE_SOURCE_DIR}
)


find_package(GTest CONFIG REQUIRED)
include(GoogleTest)

add_executable(compiledb4ms_test
  command_object.h
  command_object.cpp
  command_object.test.cpp
)
target_include_directories(compiledb4ms_test
  PRIVATE ${CMAKE_SOURCE_DIR}
)
target_link_libraries(compiledb4ms_test
  GTest::gtest_main
)
gtest_discover_tests(compiledb4ms_test)
