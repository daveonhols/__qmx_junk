cmake_minimum_required (VERSION 2.6)
project (CMAKETEST C CXX)
include_directories(include lib)

add_subdirectory(googletest)

add_executable(example test/example.cpp test/TestQConn.cpp src/QConn.cpp)
target_link_libraries(example gtest_main)
add_test(NAME example_test COMMAND example)

find_package( Threads )

add_executable(server src/server.cpp src/SimpleSocket.cpp src/Connections.cpp src/QConn.cpp src/QInstance.cpp src/ByteReader.cpp src/AsyncLoginHandler.cpp src/Handlers.cpp src/ListenServer.cpp src/QMXListenServer.cpp src/Socket.cpp src/ISocket.cpp)
target_link_libraries(server ${CMAKE_THREAD_LIBS_INIT} )
