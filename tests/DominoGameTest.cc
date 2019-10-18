#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "DominoGame.h"
#include "Tile.h"
#include "Player.h"

TEST_CASE("DominoGame Constructor (Arguments)") {
    Player Pablo("pablorg99", "pablorg99pass");
    Player Francis("francisjmp", "francisjmppass");
    REQUIRE_NOTHROW(DominoGame Game(Pablo, Francis));
}

TEST_CASE("DominoGame Constructor (fillDrawPile_)") {
    Player Pablo("pablorg99", "pablorg99pass");
    Player Francis("francisjmp", "francisjmppass");
    DominoGame Game(Pablo, Francis);
    REQUIRE(Game.getDrawPile().at(0) == Tile firstTileInPile(6,6));
}