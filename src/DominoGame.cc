#include "DominoGame.h"

#include <iostream>
using namespace std;

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

string DominoGame::getBoardString() const {
    string boardTiles = "";
    list <Tile> :: const_iterator tile;
    // Using getBoard instead of board_ causes problems
    for (tile = board_.begin(); tile != board_.end(); tile++) {
        boardTiles += tile->tileToString();
    }
    return boardTiles;
}

void DominoGame::dealTiles() {
    for (int i = 0; i < 7; i++) {
        firstPlayer_->addTile(drawRandomTile());
        secondPlayer_->addTile(drawRandomTile());
    }
}

bool DominoGame::canPutAtLeastOneTile(Player *player) {
    vector<Tile>::const_iterator tile;
    
    for (tile = player->myTiles_.begin(); tile != player->myTiles_.end(); ++tile) {
        if(canPutTile(*tile)) {
            return true;
        }
    }
    return false;
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

bool DominoGame::putTile(Player *player, Tile tile, string boardside) {
    if(boardside == "right") {
        if(canPutTile(tile)){
            addTileAtBack(tile);
        }
        else if(canPutTile(tile.flippedTile())) {
            addTileAtBack(tile.flippedTile());
        }
        else {
            return false;
        }
    } 
    else if(boardside == "left") {
        if(canPutTile(tile)) {
            addTileAtFront(Tile(tile));
        }
        else if(canPutTile(tile.flippedTile())) {
            addTileAtFront(tile.flippedTile());
        }
        else {
            return false;
        }
    }
    player->deleteTile(tile);
    return true;
}

bool DominoGame::canPutTile(const Tile tile) {
    if(getBoard().size() == 0){
        return true;
    }
    Tile leftside = board_.front();
    Tile rightside = board_.back();
    
    if((tile.compatibleTile(rightside.getRight())) or (tile.compatibleTile(leftside.getLeft()))) {
        return true;
    }
    return false;
}

bool DominoGame::findTileInTiles(const vector<Tile> tilesVector, const Tile tileToFind){
    if(find(tilesVector.begin(), tilesVector.end(), tileToFind) != tilesVector.end()){
        return true;
    }
    return false;
}

Player DominoGame::firstPlayerToPlay(){
    vector<Tile> firstPlayerTiles = firstPlayer_->getPlayerTiles();
    vector<Tile> secondPlayerTiles = secondPlayer_->getPlayerTiles();
    for (int tileIndex = 6; tileIndex > 0; --tileIndex) {
        if(findTileInTiles(firstPlayerTiles, Tile(tileIndex,tileIndex))){
            return *firstPlayer_;
        }
        else if(findTileInTiles(secondPlayerTiles, Tile(tileIndex,tileIndex))){
            return *secondPlayer_;
        }
    }
    int firstPlayerGreatestTileValue = firstPlayer_->greatestTileValue();
    int secondPlayerGreatestTileValue = secondPlayer_->greatestTileValue();
    if(firstPlayerGreatestTileValue > secondPlayerGreatestTileValue) {
        firstPlayer_->setTurnToTrue();
        return *firstPlayer_;
    }
    else {
        secondPlayer_->setTurnToTrue();
        return *secondPlayer_;
    }
}

void DominoGame::passTurn() {
    if (firstPlayer_->getTurn()) {
        firstPlayer_->setTurnToFalse();
        secondPlayer_->setTurnToTrue();
    }
    else {
        firstPlayer_->setTurnToTrue();
        secondPlayer_->setTurnToFalse();
    }
}

