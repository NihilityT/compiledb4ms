find_package(pugixml CONFIG REQUIRED)

add_library(libcompiledb4ms STATIC
  command_object.h
  command_object.cpp
  vcxproj.h
  vcxproj.cpp
)
target_include_directories(libcompiledb4ms
  PUBLIC ${CMAKE_SOURCE_DIR}
)
target_link_libraries(libcompiledb4ms
  PUBLIC pugixml::pugixml
)


find_package(GTest CONFIG REQUIRED)
include(GoogleTest)

add_executable(libcompiledb4ms_test
  command_object.test.cpp
  vcxproj.test.cpp
)
target_link_libraries(libcompiledb4ms_test
  PRIVATE GTest::gtest_main
  PRIVATE libcompiledb4ms
)
gtest_discover_tests(libcompiledb4ms_test
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

