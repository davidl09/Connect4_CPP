cmake_minimum_required(VERSION 3.22)
project(Connect4_CPP)

include_directories(include)

add_compile_options(-O3 -std=c++20 -mtune=native)

add_executable(connect-4 main.cpp)
