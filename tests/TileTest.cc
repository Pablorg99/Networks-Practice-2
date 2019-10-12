#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "Tile.h"

TEST_CASE("Tile values out of range") {
    REQUIRE_THROWS(Tile(-1,6));
    REQUIRE_THROWS(Tile(-1,-1));
    REQUIRE_THROWS(Tile(-1,7));
    REQUIRE_THROWS(Tile(1,-1));
    REQUIRE_THROWS(Tile(7,-1));
    REQUIRE_THROWS(Tile(8,2));
}

TEST_CASE("Tile construction is OK") {
    REQUIRE_NOTHROW(Tile validTile(4,6));
    REQUIRE_NOTHROW(Tile validTile(2,6));
    REQUIRE_NOTHROW(Tile validTile(0,0));
}

TEST_CASE("Tile getters") {
    Tile validTile1(2,3);
    Tile validTile2(0,6);
    REQUIRE(validTile1.getLeft() == 2);
    REQUIRE(validTile1.getRight() == 3);
    REQUIRE(validTile2.getLeft() == 0);
    REQUIRE(validTile2.getRight() == 6);
}

TEST_CASE("Flip tile") {
    Tile validTile(2,3);
    REQUIRE(validTile.getLeft() == 2);
    REQUIRE(validTile.getRight() == 3);
    REQUIRE_NOTHROW(validTile.flipTile());
    REQUIRE(validTile.getLeft() == 3);
    REQUIRE(validTile.getRight() == 2);
}