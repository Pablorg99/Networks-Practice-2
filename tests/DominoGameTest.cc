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

TEST_CASE("drawRandomTile removes the tile from the draw pile") {
    Player Pablo("pablorg99", "pablorg99pass");
    Player Francis("francisjmp", "francisjmppass");
    DominoGame Game(&Pablo, &Francis);
    
    CHECK(Game.getTilesLeftInPile() == 28);
    Tile auxiliarTile(Game.drawRandomTile());
    for (int i = 0; i < Game.getTilesLeftInPile(); i++) {
        CHECK_FALSE(auxiliarTile == Game.getDrawPile()[i]);
    }
    CHECK(Game.getTilesLeftInPile() == 27);
}

TEST_CASE("canPutAtLeastOneTile indicates if a player can put any of its tiles in the game"){
    Player Pablo("pablorg99","pablorg99pass");
    Player Francis("francisjmp", "francisjmppass");
    DominoGame Game(&Pablo, &Francis);

    Game.addTileAtBack(Tile(3,4));
    Game.addTileAtBack(Tile(4,5));
    Game.addTileAtBack(Tile(5,6));
    Pablo.addTile(Tile(1,2));
    CHECK_FALSE(Game.canPutAtLeastOneTile(&Pablo));
    Pablo.addTile(Tile(3,5));
    CHECK(Game.canPutAtLeastOneTile(&Pablo));
}

TEST_CASE("canPutTile indicates if a tile can be put in the board"){
    Player Pablo("pablorg99","pablorg99pass");
    Player Francis("francisjmp", "francisjmppass");
    DominoGame Game(&Pablo, &Francis);
    
    Game.addTileAtBack(Tile(2,3));
    Game.addTileAtBack(Tile(3,4));
    Game.addTileAtBack(Tile(4,5));
    CHECK_FALSE(Game.canPutTile(Tile(4,4)));
    CHECK_FALSE(Game.canPutTile(Tile(1,1)));
    CHECK(Game.canPutTile(Tile(2,2)));
    CHECK(Game.canPutTile(Tile(5,5)));
    CHECK(Game.canPutTile(Tile(2,4)));
    CHECK(Game.canPutTile(Tile(5,3)));
}

TEST_CASE("putTile updates the number of player tiles and tiles onboard"){
    Player Pablo("pablorg99","pablorg99pass");
    Player Francis("francisjmp", "francisjmppass");
    DominoGame Game(&Pablo, &Francis);
    Game.dealTiles();
    Pablo.addTile(Tile(5,4));
    CHECK(Pablo.getPlayerTiles().size() == 8);
    Game.addTileAtBack(Tile(4,4));
    CHECK(Game.getBoard().size() == 1);
    Game.putTile(&Pablo, Tile(5,4), "right side");
    CHECK(Pablo.getPlayerTiles().size() == 7);
    CHECK(Game.getBoard().size() == 2);
}
