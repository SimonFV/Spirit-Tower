cmake_minimum_required(VERSION 3.8)

project(st_server)

set(CMAKE_CXX_STANDARD_REQUIRED 14)

set(src 
    src/main.cpp
    src/server.cpp
    src/process.cpp
)

set(head
    include/server.hpp
)

include_directories(${PROJECT_SOURCE_DIR}/include/)


add_executable(run ${src} ${head})