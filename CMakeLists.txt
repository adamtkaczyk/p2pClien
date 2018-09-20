cmake_minimum_required(VERSION 2.8)

SET(CMAKE_BUILD_TYPE Debug)

project(P2PClient)

include_directories("/home/adamtkaczyk/project/googletest-master/googletest/include/")

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

find_package (Threads)
find_package(Boost COMPONENTS system REQUIRED)

add_executable(${PROJECT_NAME} "src/p2pnodeapp.cpp" 
	                       "src/p2pnode.cpp" 
                               "src/p2pnode.h"
                               "src/remotenode.cpp"
                               "src/remotenode.h"
                               "src/sessionmanager.cpp"
                               "src/sessionmanager.h"
			       "src/networking/tcpserver.cpp" 
			       "src/networking/tcpserver.h"
			       "src/networking/tcpconnection.cpp"
			       "src/networking/tcpconnection.h")

add_executable(${PROJECT_NAME}_test "src/p2pnodeapp_test.cpp")

target_link_libraries (${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries (${PROJECT_NAME} ${Boost_SYSTEM_LIBRARY})
target_link_libraries (${PROJECT_NAME}_test ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries (${PROJECT_NAME}_test "/home/adamtkaczyk/project/googletest-master/build/googlemock/gtest/libgtest.a"
                                            "/home/adamtkaczyk/project/googletest-master/build/googlemock/gtest/libgtest_main.a")
