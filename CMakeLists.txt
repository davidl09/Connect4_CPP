cmake_minimum_required(VERSION 3.22)
project(Connect4_CPP)
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)

include_directories(include)
add_subdirectory(SDL)

add_executable(connect-4 main.cpp)

target_include_directories(connect-4 PUBLIC SDL2::SDL2_include_dirs)

target_link_libraries(connect-4 PUBLIC SDL2::SDL2)
