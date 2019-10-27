#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "Player.h"

#include <vector>
using std::vector;

TEST_CASE("Player construction is OK") {
    CHECK_NOTHROW(Player validPlayer("pablorg","pablopass", 1));
    CHECK_NOTHROW(Player validPlayer("francismp","francispass", 2));
    CHECK_NOTHROW(Player validPlayer("sergiobachiller","sergiopass", 3));
}

TEST_CASE("Adding/Getting tile (as Tile object) to player is OK"){
    Player newPlayer("player", "playerpass", 1);
    vector<Tile> playerTiles = {Tile(2,4)};
    newPlayer.addTile(Tile(2,4));
    CHECK(newPlayer.getPlayerTiles() == playerTiles);
    newPlayer.addTile(Tile(3,3));
    playerTiles.push_back(Tile(3,3));
    CHECK(newPlayer.getPlayerTiles() == playerTiles);
    newPlayer.addTile(Tile(1,6));
    playerTiles.push_back(Tile(1,6));
    CHECK(newPlayer.getPlayerTiles() == playerTiles);
}

TEST_CASE("Getting tile as string from player is OK"){
    Player newPlayer("player", "playerpass", 1);
    newPlayer.addTile(Tile(2,4));
    CHECK(newPlayer.getPlayerTilesString() == "|2|4|");
    newPlayer.addTile(Tile(3,3));
    CHECK(newPlayer.getPlayerTilesString() == "|2|4||3|3|");
    newPlayer.addTile(Tile(1,6));
    CHECK(newPlayer.getPlayerTilesString() == "|2|4||3|3||1|6|");
}

TEST_CASE("greatestTileValue should return the addition of the greatest tile values"){
    Player newPlayer("player", "playerpass", 1);
    newPlayer.addTile(Tile(2,4));
    CHECK(newPlayer.greatestTileValue() == 6);
    newPlayer.addTile(Tile(6,6));
    CHECK(newPlayer.greatestTileValue() == 12);
    newPlayer.addTile(Tile(6,4));
    CHECK(newPlayer.greatestTileValue() == 12);
}