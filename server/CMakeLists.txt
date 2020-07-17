cmake_minimum_required(VERSION 3.8)

project(st_server)

set(CMAKE_CXX_STANDARD_REQUIRED 14)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/external/CMake-codecov/cmake" ${CMAKE_MODULE_PATH})

set(src 
    src/main.cpp
    src/server.cpp
    src/game.cpp
    src/enemies.cpp
    #src/genetic_algorithm.cpp
    #src/bresenham_algorithm.cpp
    #src/backtracking.cpp
    #src/a-star.cpp
)

set(head
    include/server.hpp
    include/game.hpp
    include/player.hpp
    include/ghost.hpp
)

include_directories(${PROJECT_SOURCE_DIR}/include/)

#Test
enable_testing()
add_subdirectory(googletest)

#Logging
add_subdirectory(external/spdlog)

add_library(server_library ${head} ${src})

add_executable(run ${src} ${head})

#Threads
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

target_link_libraries(run spdlog Threads::Threads)
target_link_libraries(server_library spdlog)

#Test
add_subdirectory(test)

