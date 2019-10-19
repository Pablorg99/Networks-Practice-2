#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "Player.h"

#include <vector>
using std::vector;

TEST_CASE("Player construction is OK") {
    CHECK_NOTHROW(Player validPlayer("pablorg","pablopass"));
    CHECK_NOTHROW(Player validPlayer("francismp","francispass"));
    CHECK_NOTHROW(Player validPlayer("sergiobachiller","sergiopass"));
}

TEST_CASE("Adding/Getting tile (as Tile object) to player is OK"){
    Player newPlayer("player", "playerpass");
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
    Player newPlayer("player", "playerpass");
    newPlayer.addTile(Tile(2,4));
    CHECK(newPlayer.getPlayerTilesString() == "|2|4|");
    newPlayer.addTile(Tile(3,3));
    CHECK(newPlayer.getPlayerTilesString() == "|2|4||3|3|");
    newPlayer.addTile(Tile(1,6));
    CHECK(newPlayer.getPlayerTilesString() == "|2|4||3|3||1|6|");
}