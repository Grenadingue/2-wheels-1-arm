cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
include(${CMAKE_CURRENT_SOURCE_DIR}/socket.io-client-cpp/CMakeLists.txt)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
