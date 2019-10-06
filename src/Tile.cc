#include "Tile.h"
#include <cstdlib>

Tile::Tile(int leftValue, int rightValue) {
    left_ = leftValue;
    right_ = rightValue;
}

void Tile::flipTile() {
    int aux;
    aux = left_;
    left_ = right_;
    right_ = aux;
}