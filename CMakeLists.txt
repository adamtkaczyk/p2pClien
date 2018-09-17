cmake_minimum_required(VERSION 2.8)

if(NOT DEFINED CMAKE_C_COMPILER)
  SET(CMAKE_C_COMPILER /home/adamtkaczyk/project/gcc-8.1.0/objdir/bin/gcc)
endif()

if(NOT DEFINED CMAKE_CXX_COMPILER)
  SET(CMAKE_CXX_COMPILER /home/adamtkaczyk/project/gcc-8.1.0/objdir/bin/g++)
endif()

SET(CMAKE_BUILD_TYPE Debug)
project(P2PClient)

include_directories("/home/adamtkaczyk/project/googletest-master/googletest/include/")

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

find_package (Threads)

add_executable(${PROJECT_NAME} "p2pnodeapp.cpp" "p2pnode.cpp" "p2pnode.h")
add_executable(${PROJECT_NAME}_test "p2pnodeapp_test.cpp")

target_link_libraries (${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries (${PROJECT_NAME}_test ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries (${PROJECT_NAME}_test "/home/adamtkaczyk/project/googletest-master/build/googlemock/gtest/libgtest.a"
                                      "/home/adamtkaczyk/project/googletest-master/build/googlemock/gtest/libgtest_main.a")
