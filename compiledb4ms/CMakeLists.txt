add_executable(compiledb4ms
  main.cpp
)
target_include_directories(compiledb4ms
  PRIVATE ${CMAKE_SOURCE_DIR}
)
target_link_libraries(compiledb4ms
  PRIVATE libcompiledb4ms
)

install(TARGETS compiledb4ms)
