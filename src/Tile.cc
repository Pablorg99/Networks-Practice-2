#include "Tile.h"

Tile::Tile(int leftValue, int rightValue) {
    if ((leftValue < 0) or (leftValue > 6) or (rightValue < 0) or (rightValue > 6)) {
        throw "Invalid tile values";
    }
    left_ = leftValue;
    right_ = rightValue;
}

Tile Tile::flippedTile() {
    Tile newTile(right_, left_);
    return newTile;
}

bool Tile::operator==(const Tile TileAtRight) const {
    if(this->getLeft() == TileAtRight.getLeft() and this->getRight() == TileAtRight.getRight()) {
        return true;
    }

    if(this->getLeft() == TileAtRight.getRight() and this->getRight() == TileAtRight.getLeft()) {
        return true;
    }

    return false;   
}

bool Tile::compatibleTile(int value) const {
    if((this->getLeft() == value) or (this->getRight() == value)) {
        return true;
    }
    return false;
}