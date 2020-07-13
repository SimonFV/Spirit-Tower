cmake_minimum_required(VERSION 3.8)

project(st_server)

set(CMAKE_CXX_STANDARD_REQUIRED 14)

set(src 
    src/main.cpp
    #src/server.cpp
    #src/game.cpp
    #src/enemies.cpp
    #src/genetic_algorithm.cpp
    #src/bresenham_algorithm.cpp
    #src/backtracking.cpp
    #src/a-star.cpp
)

set(head
    #include/server.hpp
    #include/game.hpp
    #include/player.hpp
    #include/ghost.hpp
)

include_directories(${PROJECT_SOURCE_DIR}/include/)


add_executable(run ${src} ${head})

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(run Threads::Threads)