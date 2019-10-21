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
    
    CHECK(Game.getDrawPile().size() == 14);
    CHECK(Pablo.getPlayerTiles().size() == 7);
    CHECK(Francis.getPlayerTiles().size() == 7);
}

TEST_CASE("getTilesLeftInPile is equal to drawPile size") {
    Player Pablo("pablorg99", "pablorg99pass");
    Player Francis("francisjmp", "francisjmppass");
    DominoGame Game(&Pablo, &Francis);
    
    CHECK(Game.getDrawPile().size() == 14);
    CHECK(Game.getTilesLeftInPile() == 14);
}

TEST_CASE("getRandomTile removes the tile from the draw pile") {
    Player Pablo("pablorg99", "pablorg99pass");
    Player Francis("francisjmp", "francisjmppass");
    DominoGame Game(&Pablo, &Francis);

    CHECK(Game.getTilesLeftInPile() == 14);
    Tile auxiliarTile(Game.getRandomTile());
    for (int i = 0; i < Game.getTilesLeftInPile(); i++) {
        CHECK_FALSE(auxiliarTile == Game.getDrawPile()[i]);
    }
    CHECK(Game.getTilesLeftInPile() == 13);
}

/*
TEST_CASE("checkPutAnyTile indicates if a player can put any of its tiles in the game"){
    Player Pablo("pablorg99","pablorg99pass");
    Player Francis("francisjmp", "francisjmppass");
    DominoGame Game(&Pablo, &Francis);
    Pablo.addTile(Tile(7,7));
    Game.getBoardTiles().push_back(Tile(7,7));
    
    CHECK(Game.checkPutAnyTile(&Pablo, "rightside") == true);
 }

TEST_CASE("checkPutTile indicates if a player can put a certain tile in the game"){
    Player Pablo("pablorg99","pablorg99pass");
    Player Francis("francisjmp", "francisjmppass");
    DominoGame Game(&Pablo, &Francis);
    vector<Tile>::iterator it;
    Pablo.addTile(Tile(7,7));
    Game.getBoardTiles().push_back(Tile(7,7));
    
    CHECK(Game.checkPutTile(&Pablo, Tile(7,7), "rightside") == true);
 }
 */

TEST_CASE("putTile updates the player tiles and the board Tiles"){
    Player Pablo("pablorg99","pablorg99pass");
    Player Francis("francisjmp", "francisjmppass");
    DominoGame Game(&Pablo, &Francis);
    Pablo.addTile(Tile(5,4));
    CHECK(Game.getBoardTiles().size() == 0);
    CHECK(Pablo.getPlayerTiles().size() == 8);
    Game.getBoardTiles().insert(Game.getBoardTiles().begin(), Tile(4,4));
    CHECK(Game.getBoardTiles().size() == 1);
    Game.putTile(&Pablo, Tile(5,4), "rightside");
    CHECK(Pablo.getPlayerTiles().size() == 7);
    CHECK(Game.getBoardTiles().size() == 2);
}
