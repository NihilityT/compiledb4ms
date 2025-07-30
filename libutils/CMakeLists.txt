add_library(libutils STATIC
  utils.h
  utils.cpp
)
target_include_directories(libutils
  PUBLIC ${CMAKE_SOURCE_DIR}
)


find_package(GTest CONFIG REQUIRED)
include(GoogleTest)

add_executable(libutils_test
  utils.test.cpp
)
target_link_libraries(libutils_test
  PRIVATE GTest::gtest_main
  PRIVATE libutils
)
gtest_discover_tests(libutils_test
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)
