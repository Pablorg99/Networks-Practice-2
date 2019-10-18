cmake_minimum_required(VERSION 3.10)
project(Networks-Practice-2)
enable_testing()

set(CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++${CXX_STANDARD}")

# Public libraries
include_directories(public/)
# Internal libraries
include_directories(src/include/)

list(APPEND SRC_FILES
    DominoGame
    Player
    Tile
)

foreach(SRC ${SRC_FILES})
    add_executable(${SRC}Test tests/${SRC}Test.cc)
    add_library(${SRC}Lib src/${SRC}.cc)
    target_link_libraries(${SRC}Test ${SRC}Lib)
    add_test(${SRC}Test ${SRC}Test)
endforeach()
