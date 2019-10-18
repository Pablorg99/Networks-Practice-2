#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "Player.h"

#include <vector>
using std::vector;

TEST_CASE("Player construction is OK") {
    vector <Tile> tilesVector;
    REQUIRE_NOTHROW(Player validPlayer("pablorg","pablopass", tilesVector));
    REQUIRE_NOTHROW(Player validPlayer("francismp","francispass", tilesVector));
    REQUIRE_NOTHROW(Player validPlayer("sergiobachiller","sergiopass", tilesVector));
}

TEST_CASE("Adding/Getting tile (as Tile object) to player is OK"){
    Player newPlayer;
    vector<Tile> playerTiles = {Tile(2,4)};
    newPlayer.addTile(2,4);
    REQUIRE(newPlayer.getPlayerTiles() == playerTiles)
    newPlayer.addTile(3,3);
    playerTiles.push_back(Tile(3,3));
    REQUIRE(newPlayer.getPlayerTiles() == playerTiles)
    newPlayer.addTile(1,6);
    playerTiles.push_back(Tile(1,6));
    REQUIRE(newPlayer.getPlayerTiles() == playerTiles)
}

TEST_CASE("Getting tile as string from player is OK"){
    Player newPlayer;
    newPlayer.addTile(2,4);
    REQUIRE(newPlayer.getPlayerTilesString() == "|2|4|")
    newPlayer.addTile(3,3);
    REQUIRE(newPlayer.getPlayerTilesString() == "|2|4||3|3|")
    newPlayer.addTile(1,6);
    REQUIRE(newPlayer.getPlayerTilesString() == "|2|4||3|3||1|6|")
}