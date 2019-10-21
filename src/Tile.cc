#include "Tile.h"

Tile::Tile(int leftValue, int rightValue) {
    if ((leftValue < 0) or (leftValue > 6) or (rightValue < 0) or (rightValue > 6)) {
        throw "Invalid tile values";
    }
    left_ = leftValue;
    right_ = rightValue;
}

void Tile::flipTile() {
    int aux;
    aux = left_;
    left_ = right_;
    right_ = aux;
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

bool Tile::compatibleTiles(Tile tile){
    if(this->getLeft() == tile.getLeft()){
        return true;
    }
    this->flipTile();
    if(this->getLeft() == tile.getLeft()){
        return true;
    }
    return false;
}