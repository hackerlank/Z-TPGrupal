cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 11)
project(Z_TPGrupal)

set(COMMON_FILES
        Lock.cpp
        Lock.h
        messenger.cpp
        messenger.h
        socket.cpp
        socket.h
        socketError.cpp
        socketError.h
        Thread.cpp
        Thread.h
        split.cpp
        split.h
        ../../test/clientReceiverTest.cpp ../../test/clientReceiverTest.h)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
add_library(common ${COMMON_FILES})