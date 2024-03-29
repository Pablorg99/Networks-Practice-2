cmake_minimum_required(VERSION 3.0)
project(Networks-Practice-2)
enable_testing()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -pthread -Wall")

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
add_library(ServerLib src/Server.cc)
add_library(ServerMainLib ServerMain.cc)
add_library(ClientLib src/Client.cc)
add_library(ClientMainLib ClientMain.cc)
add_library(DominoGameHandlerLib src/DominoGameHandler.cc)

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

# Build MainServer executable
add_executable(ServerMain.out ServerMain.cc)
target_link_libraries(ServerMain.out ServerMainLib)
target_link_libraries(ServerMain.out ServerLib)
target_link_libraries(ServerLib DominoGameHandlerLib)
target_link_libraries(DominoGameHandlerLib DominoGameLib)
target_link_libraries(DominoGameHandlerLib TileLib)
target_link_libraries(DominoGameHandlerLib PlayerLib)

# Build ClientMain executable
add_executable(ClientMain.out ClientMain.cc)
target_link_libraries(ClientMain.out ClientMainLib)
target_link_libraries(ClientMain.out ClientLib)
