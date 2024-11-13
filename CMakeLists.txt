cmake_minimum_required(VERSION 3.25)
project(Connect4_CPP)

set(CMAKE_CXX_STANDARD 20)

add_executable(connect-4 main.cpp)
add_executable(connect-4-benchmark benchmark.cpp)

target_include_directories(connect-4 PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(connect-4-benchmark PUBLIC ${CMAKE_SOURCE_DIR}/include)