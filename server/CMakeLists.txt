cmake_minimum_required(VERSION 3.8)

project(st_server)

set(CMAKE_CXX_STANDARD_REQUIRED 11)

set(src 
    src/main.cpp
    src/server.cpp
    src/game.cpp
    src/enemies.cpp
    src/genetic_algorithm.cpp
    src/bresenham_algorithm.cpp
    src/backtracking.cpp
    src/a-star.cpp
)

set(head
    include/server.hpp
    include/game.hpp
    include/player.hpp
    include/ghost.hpp
    include/algorithms.hpp
)

include_directories(${PROJECT_SOURCE_DIR}/include/)


#Logging
add_subdirectory(spdlog)


# Code Coverage
add_library(coverage_config INTERFACE)

option(CODE_COVERAGE "Enable coverage reporting" OFF)
if(CODE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  # Add required flags (GCC & LLVM/Clang)
  target_compile_options(coverage_config INTERFACE
    -O0        # no optimization
    -g         # generate debug info
    --coverage # sets all required flags
  )
  if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.13)
    target_link_options(coverage_config INTERFACE --coverage)
  else()
    target_link_libraries(coverage_config INTERFACE --coverage)
  endif()
endif(CODE_COVERAGE)


add_library(server_library ${head} ${src})

add_executable(run ${src} ${head})

#Threads
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

target_link_libraries(run spdlog Threads::Threads)
target_link_libraries(server_library PUBLIC coverage_config spdlog)


#Coverage


option (BUILD_TESTING "Build the testing tree." ON)
# Only build tests if we are the top-level project
# Allows this to be used by super projects with `add_subdirectory`
if (BUILD_TESTING AND (PROJECT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR))
    enable_testing()
    add_subdirectory(googletest)
    add_subdirectory(test)
endif()

