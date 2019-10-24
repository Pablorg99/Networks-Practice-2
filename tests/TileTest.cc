#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "Tile.h"

TEST_CASE("Tile values out of range") {
    CHECK_THROWS(Tile(-1,6));
    CHECK_THROWS(Tile(-1,-1));
    CHECK_THROWS(Tile(-1,7));
    CHECK_THROWS(Tile(1,-1));
    CHECK_THROWS(Tile(7,-1));
    CHECK_THROWS(Tile(8,2));
}

TEST_CASE("Tile construction is OK") {
    CHECK_NOTHROW(Tile validTile(4,6));
    CHECK_NOTHROW(Tile validTile(2,6));
    CHECK_NOTHROW(Tile validTile(0,0));
}

TEST_CASE("Tile getters") {
    Tile validTile1(2,3);
    Tile validTile2(0,6);
    CHECK(validTile1.getLeft() == 2);
    CHECK(validTile1.getRight() == 3);
    CHECK(validTile2.getLeft() == 0);
    CHECK(validTile2.getRight() == 6);
}

TEST_CASE("Flip tile") {
    Tile validTile(2,3);
    CHECK(validTile.getLeft() == 2);
    CHECK(validTile.getRight() == 3);
    CHECK(validTile.flippedTile().getLeft() == 3);
    CHECK(validTile.flippedTile().getRight() == 2);
}

TEST_CASE("== Operator") {
    Tile EqualTile1(2,3);
    Tile EqualTile2(2,3);
    Tile DifferentTile(2,4);
    Tile EqualFlippedTile(3,2);
    CHECK(EqualTile1 == EqualTile2);
    CHECK_FALSE(EqualTile1 == DifferentTile);
    CHECK(EqualTile1 == EqualFlippedTile);
}

TEST_CASE("Get tile value"){
    Tile tile(2,4);
    CHECK(tile.getTileValue() == 6);
}