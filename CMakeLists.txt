cmake_minimum_required(VERSION 3.0)
project(Networks-Practice-2)
enable_testing()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# Public libraries
include_directories(public/)
# Internal libraries
include_directories(src/include/)


# Build all object files and libraries
add_library(DominoGameLib src/DominoGame.cc)
add_library(TileLib src/Tile.cc)
add_library(PlayerLib src/Player.cc)
add_library(DominoGameTestLib tests/DominoGameTest.cc)
add_library(TileTestLib tests/TileTest.cc)
add_library(PlayerTestLib tests/PlayerTest.cc)


# Build TileTest executable
add_executable(TileTest tests/TileTest.cc)
target_link_libraries(TileTest TileLib)
add_test(TileTest TileTest)

# Build PlayerTest executable
add_executable(PlayerTest tests/PlayerTest.cc)
target_link_libraries(PlayerTest PlayerLib)
target_link_libraries(PlayerTest TileLib)
add_test(PlayerTest PlayerTest)

# Build DominoGameTest executable
add_executable(DominoGameTest tests/DominoGameTest.cc)
target_link_libraries(DominoGameTest DominoGameLib)
target_link_libraries(DominoGameTest DominoGameTestLib)
target_link_libraries(DominoGameTest TileLib)
target_link_libraries(DominoGameTest PlayerLib)
add_test(DominoGameTest DominoGameTest)
