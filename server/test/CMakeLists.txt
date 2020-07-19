cmake_minimum_required(VERSION 3.8)
project(unit_tests)

SET(GCC_COVERAGE_COMPILE_FLAGS "-fprofile-arcs -ftest-coverage")
SET(GCC_COVERAGE_LINK_FLAGS    "-lgcov")

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

set(src
  serverTest.cpp
)

add_executable(server_test ${src})

target_link_libraries(server_test PUBLIC
  gtest_main
  server_library
  gtest
  gmock
)