#include "DominoGame.h"
#include<algorithm>

DominoGame::DominoGame(Player *firstPlayer, Player *secondPlayer):
    firstPlayer_(firstPlayer),
    secondPlayer_(secondPlayer)
{
    srand(time(NULL));
    tilesLeftInPile_ = 28;
    drawPile_.reserve(tilesLeftInPile_);
    fillDrawPile_();
}

void DominoGame::fillDrawPile_() {
    drawPile_.insert(drawPile_.begin(), Tile(6,6));
    drawPile_.insert(drawPile_.begin() + 1, Tile(6,5));
    drawPile_.insert(drawPile_.begin() + 2, Tile(6,4));
    drawPile_.insert(drawPile_.begin() + 3, Tile(6,3));
    drawPile_.insert(drawPile_.begin() + 4, Tile(6,2));
    drawPile_.insert(drawPile_.begin() + 5, Tile(6,1));
    drawPile_.insert(drawPile_.begin() + 6, Tile(6,0));
    drawPile_.insert(drawPile_.begin() + 7, Tile(5,5));
    drawPile_.insert(drawPile_.begin() + 8, Tile(5,4));
    drawPile_.insert(drawPile_.begin() + 9, Tile(5,3));
    drawPile_.insert(drawPile_.begin() + 10, Tile(5,2));
    drawPile_.insert(drawPile_.begin() + 11, Tile(5,1));
    drawPile_.insert(drawPile_.begin() + 12, Tile(5,0));
    drawPile_.insert(drawPile_.begin() + 13, Tile(4,4));
    drawPile_.insert(drawPile_.begin() + 14, Tile(4,3));
    drawPile_.insert(drawPile_.begin() + 15, Tile(4,2));
    drawPile_.insert(drawPile_.begin() + 16, Tile(4,1));
    drawPile_.insert(drawPile_.begin() + 17, Tile(4,0));
    drawPile_.insert(drawPile_.begin() + 18, Tile(3,3));
    drawPile_.insert(drawPile_.begin() + 19, Tile(3,2));
    drawPile_.insert(drawPile_.begin() + 20, Tile(3,1));
    drawPile_.insert(drawPile_.begin() + 21, Tile(3,0));
    drawPile_.insert(drawPile_.begin() + 22, Tile(2,2));
    drawPile_.insert(drawPile_.begin() + 23, Tile(2,1));
    drawPile_.insert(drawPile_.begin() + 24, Tile(2,0));
    drawPile_.insert(drawPile_.begin() + 25, Tile(1,1));
    drawPile_.insert(drawPile_.begin() + 26, Tile(1,0));
    drawPile_.insert(drawPile_.begin() + 27, Tile(0,0));
}

Tile DominoGame::drawRandomTile() {
    if (tilesLeftInPile_ > 0) {
        int randomTileIndex = rand() % tilesLeftInPile_;

        Tile auxiliarTile = drawPile_[randomTileIndex];
        drawPile_.erase(drawPile_.begin() + randomTileIndex);
        tilesLeftInPile_ = tilesLeftInPile_ - 1;

        return auxiliarTile;
    }
    else throw "There are no tiles in the draw pile";
}

void DominoGame::dealTiles() {
    for (int i = 0; i < 7; i++) {
        firstPlayer_->addTile(drawRandomTile());
        secondPlayer_->addTile(drawRandomTile());
    }
}

bool DominoGame::canPutAtLeastOneTile(Player *player) {
    vector<Tile>::iterator it;
    
    for (it = player->getPlayerTiles().begin(); it != player->getPlayerTiles().end(); ++it) {
        if(canPutTile(*it)) {
            return true;
        }
    }
    return false;
}

bool DominoGame::canPutTile(const Tile tile) {
    Tile leftside = board_.front();
    Tile rightside = board_.back();
    
    if((tile.compatibleTile(rightside.getRight())) or (tile.compatibleTile(leftside.getLeft()))) {
            return true;
    }
    return false;
}


void DominoGame::putTile(Player *player, Tile tile, string boardside) {
    if(boardside == "right side"){
        if(canPutTile(tile)){
            board_.push_back(Tile(tile));
        }
        else if(canPutTile(tile.flippedTile())) {
            board_.push_back(tile.flippedTile());
        }
    }
    else
    {
        if(canPutTile(tile)) {
            board_.push_front(Tile(tile));
        }
        else if(canPutTile(tile.flippedTile())) {
            board_.push_front(tile.flippedTile());
        }
    }
    player->deleteTile(tile);
}