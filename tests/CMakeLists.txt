find_package(GTest CONFIG REQUIRED)
include(GoogleTest)

add_executable(acceptance_test
  usage.cpp
)
target_link_libraries(acceptance_test
  PRIVATE GTest::gtest_main
  PRIVATE libutils libcompiledb4ms
)
gtest_discover_tests(acceptance_test
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  PROPERTIES ENVIRONMENT compiledb4ms=$<TARGET_FILE:compiledb4ms>
)
