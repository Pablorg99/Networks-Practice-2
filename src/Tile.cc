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