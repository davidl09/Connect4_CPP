cmake_minimum_required(VERSION 3.27)
set(CMAKE_TOOLCHAIN_FILE "/home/davidl09/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake")
project(Connect4_CPP)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 17)

set(CMAKE_EXECUTABLE_SUFFIX ".html")

add_executable(connect4web main.cpp)

#target_compile_options(
#        connect4web PUBLIC
#        "--preload-file images"
#)

target_link_options(connect4web PRIVATE
        "-sASSERTIONS"
        "-sUSE_SDL=2"
        "-sALLOW_MEMORY_GROWTH=1"
        "-sASYNCIFY"
)

target_include_directories(connect4web PUBLIC "${CMAKE_SOURCE_DIR}/include")

set(CMAKE_EXECUTABLE_SUFFIX ".html")
