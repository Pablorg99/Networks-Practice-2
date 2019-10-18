#include "DominoGame.h"
#include <vector>
using std::vector;

DominoGame::DominoGame(Player firstPlayer, Player secondPlayer):
    firstPlayer_(firstPlayer),
    secondPlayer_(secondPlayer)
{
    srand(time(NULL));
    tilesLeftInPile_ = 28;
    fillDrawPile_();
    dealTiles_();
}

void DominoGame::fillDrawPile_() {
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
    if (tilesLeftInPile_ > 0) {
        int randomTileIndex = rand() % tilesLeftInPile_;

        Tile auxiliarTile = drawPile_[randomTileIndex];
        drawPile_.erase(drawPile_.begin() + randomTileIndex);
        tilesLeftInPile_ = tilesLeftInPile_ - 1;

        return auxiliarTile;
    }
    else throw "There are no tiles in the draw pile";
}

void DominoGame::dealTiles_() {
    for (int i = 0; i < 7; i++) {
        firstPlayer_.addTile(getRandomTile());
        secondPlayer_.addTile(getRandomTile());
    }
}