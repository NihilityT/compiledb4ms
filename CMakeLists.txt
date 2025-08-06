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

add_subdirectory(libutils)

add_subdirectory(libcompiledb4ms)
add_subdirectory(compiledb4ms)

add_subdirectory(tests)


set(CPACK_PACKAGE_NAME "compiledb4ms")
include(CPack)
