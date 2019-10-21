#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "DominoGame.h"
#include "Tile.h"
#include "Player.h"

#include <iostream>

TEST_CASE("DominoGame Constructor") {
    Player Pablo("pablorg99", "pablorg99pass");
    Player Francis("francisjmp", "francisjmppass");
    DominoGame Game(&Pablo, &Francis);
    
    CHECK(Game.getDrawPile().size() == 28);
    CHECK(Pablo.getPlayerTiles().size() == 0);
    CHECK(Francis.getPlayerTiles().size() == 0);
    Game.dealTiles();
    CHECK(Game.getDrawPile().size() == 14);
    CHECK(Pablo.getPlayerTiles().size() == 7);
    CHECK(Francis.getPlayerTiles().size() == 7);
}

TEST_CASE("getTilesLeftInPile is equal to drawPile size") {
    Player Pablo("pablorg99", "pablorg99pass");
    Player Francis("francisjmp", "francisjmppass");
    DominoGame Game(&Pablo, &Francis);
    
    CHECK(Game.getDrawPile().size() == 28);
    CHECK(Game.getTilesLeftInPile() == 28);
}

TEST_CASE("getRandomTile removes the tile from the draw pile") {
    Player Pablo("pablorg99", "pablorg99pass");
    Player Francis("francisjmp", "francisjmppass");
    DominoGame Game(&Pablo, &Francis);
    
    CHECK(Game.getTilesLeftInPile() == 28);
    Tile auxiliarTile(Game.getRandomTile());
    for (int i = 0; i < Game.getTilesLeftInPile(); i++) {
        CHECK_FALSE(auxiliarTile == Game.getDrawPile()[i]);
    }
    CHECK(Game.getTilesLeftInPile() == 27);
}

TEST_CASE("checkPutAnyTile indicates if a player can put any of its tiles in the game"){
    Player Pablo("pablorg99","pablorg99pass");
    Player Francis("francisjmp", "francisjmppass");
    DominoGame Game(&Pablo, &Francis);

    Game.addTileAtBack(Tile(3,4));
    Game.addTileAtBack(Tile(4,5));
    Game.addTileAtBack(Tile(5,6));
    Pablo.addTile(Tile(1,2));
    CHECK_FALSE(Game.checkPutAnyTile(&Pablo));
    Pablo.addTile(Tile(3,5));
    CHECK(Game.checkPutAnyTile(&Pablo));
}

TEST_CASE("checkPutTile indicates if a tile can be put in the board"){
    Player Pablo("pablorg99","pablorg99pass");
    Player Francis("francisjmp", "francisjmppass");
    DominoGame Game(&Pablo, &Francis);
    
    Game.addTileAtBack(Tile(2,3));
    Game.addTileAtBack(Tile(3,4));
    Game.addTileAtBack(Tile(4,5));
    CHECK_FALSE(Game.checkPutTile(Tile(4,4)));
    CHECK_FALSE(Game.checkPutTile(Tile(1,1)));
    CHECK(Game.checkPutTile(Tile(2,2)));
    CHECK(Game.checkPutTile(Tile(5,5)));
    CHECK(Game.checkPutTile(Tile(2,4)));
    CHECK(Game.checkPutTile(Tile(5,3)));
}

TEST_CASE("putTile updates the number of player tiles and tiles onboard"){
    Player Pablo("pablorg99","pablorg99pass");
    Player Francis("francisjmp", "francisjmppass");
    DominoGame Game(&Pablo, &Francis);
    Game.dealTiles();
    Pablo.addTile(Tile(5,4));
    CHECK(Pablo.getPlayerTiles().size() == 8);
    Game.addTileAtBack(Tile(4,4));
    CHECK(Game.getBoardTiles().size() == 1);
    Game.putTile(&Pablo, Tile(5,4), "right side");
    CHECK(Pablo.getPlayerTiles().size() == 7);
    CHECK(Game.getBoardTiles().size() == 2);
}
