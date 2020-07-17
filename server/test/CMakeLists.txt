cmake_minimum_required(VERSION 3.8)

set(src
  serverTest.cpp
)


add_executable(server_test ${src})
target_link_libraries(server_test PUBLIC
  gtest_main
  server_library
)

add_test(
  NAME server_test
  COMMAND server_test
)

if (ENABLE_COVERAGE)
      list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/CMake")
      find_package(codecov)
      add_coverage(server_test)
      list(APPEND LCOV_REMOVE_PATTERNS "/usr/")
      coverage_evaluate()
endif()