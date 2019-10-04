#include "Tile.h"
#include <cstdlib>

void Tile::setTile(const int leftValue, const int rightValue){
    left_ = leftValue;
    right_ = rightValue;
}

void Tile::flipTile(){
    int aux;
    aux = left_;
    left_ = right_;
    right_ = left_;
}



