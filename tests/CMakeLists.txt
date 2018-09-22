cmake_minimum_required(VERSION 2.8)

include_directories("/home/adamtkaczyk/project/googletest-master/googletest/include/")

find_package (Threads)

add_executable(${PROJECT_NAME}_test "p2pnodeapp_test.cpp")

target_link_libraries (${PROJECT_NAME}_test ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries (${PROJECT_NAME}_test "/home/adamtkaczyk/project/googletest-master/build/googlemock/gtest/libgtest.a"
                                            "/home/adamtkaczyk/project/googletest-master/build/googlemock/gtest/libgtest_main.a")
