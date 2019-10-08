#include "DominoGame.h"
#include <vector>
using std::vector;

DominoGame::DominoGame() {
    srand(time(NULL));
    tilesLeft_ = 28;
    drawPile_.push_back(Tile(6,6));
    drawPile_.push_back(Tile(6,5));
    drawPile_.push_back(Tile(6,4));
    drawPile_.push_back(Tile(6,3));
    drawPile_.push_back(Tile(6,2));
    drawPile_.push_back(Tile(6,1));
    drawPile_.push_back(Tile(6,0));
    drawPile_.push_back(Tile(5,5));
    drawPile_.push_back(Tile(5,4));
    drawPile_.push_back(Tile(5,3));
    drawPile_.push_back(Tile(5,2));
    drawPile_.push_back(Tile(5,1));
    drawPile_.push_back(Tile(5,0));
    drawPile_.push_back(Tile(4,4));
    drawPile_.push_back(Tile(4,3));
    drawPile_.push_back(Tile(4,2));
    drawPile_.push_back(Tile(4,1));
    drawPile_.push_back(Tile(4,0));
    drawPile_.push_back(Tile(3,3));
    drawPile_.push_back(Tile(3,2));
    drawPile_.push_back(Tile(3,1));
    drawPile_.push_back(Tile(3,0));
    drawPile_.push_back(Tile(2,2));
    drawPile_.push_back(Tile(2,1));
    drawPile_.push_back(Tile(2,0));
    drawPile_.push_back(Tile(1,1));
    drawPile_.push_back(Tile(1,0));
    drawPile_.push_back(Tile(0,0));
}

Tile DominoGame::getRandomTile() {
    if (tilesLeft_ > 0) {
        int tileIndex = rand() % tilesLeft_;
        Tile auxiliarTile(-1,-1);
        auxiliarTile = drawPile_[tileIndex];
        drawPile_.erase(drawPile_.begin() + tileIndex);
        tileIndex = tileIndex - 1;
        return auxiliarTile;
    }
    else return Tile(-1,-1);
}