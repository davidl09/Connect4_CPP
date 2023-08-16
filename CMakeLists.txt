cmake_minimum_required(VERSION 3.25)
project(Connect4_CPP)

include_directories(include)

set(CXX_STANDARD 20)

add_compile_options(-O0 -pg --std=c++20 -Wall)

add_executable(Connect4_CPP test.cpp)