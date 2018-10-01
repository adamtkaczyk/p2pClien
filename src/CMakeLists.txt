cmake_minimum_required(VERSION 2.8)

include_directories("${CMAKE_SOURCE_DIR}/src")

find_package (Threads)
find_package(Boost COMPONENTS system filesystem REQUIRED)

add_executable(${PROJECT_NAME} "p2pnodeapp.cpp" 
	                       "p2pnode.cpp" 
                               "p2pnode.h"
                               "remotenode.cpp"
                               "remotenode.h"
                               "sessionmanager.cpp"
                               "sessionmanager.h"
                               "datastruct/blockingqueue.h"
			       "networking/tcpserver.cpp" 
			       "networking/tcpserver.h"
			       "networking/tcpconnection.cpp"
                               "networking/tcpconnection.h"
                               "networking/p2pconnection.cpp"
                               "networking/p2pconnection.h"
                               "protocol/p2pmessage.cpp"
                               "protocol/p2pmessage.h"
                               "algorithm/algorithm.h")


target_link_libraries (${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries (${PROJECT_NAME} ${Boost_SYSTEM_LIBRARY})
