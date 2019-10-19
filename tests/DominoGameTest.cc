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