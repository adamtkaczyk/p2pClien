cmake_minimum_required(VERSION 2.8)

SET(CMAKE_BUILD_TYPE Debug)

project(P2PClient)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

add_subdirectory(src)
add_subdirectory(tests)
