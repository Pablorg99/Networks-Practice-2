#include "Player.h"
#include <algorithm>

Player::Player(string username, string password, int playerSocketDescriptor) {
    username_ = username;
    password_ = password;
    playerSocketDescriptor_ = playerSocketDescriptor;
    isTurn_ = false;
}

string Player::getPlayerTilesString(){
    vector<Tile>::iterator tile;
    string playerTiles = "";
    for (tile = myTiles_.begin(); tile != myTiles_.end(); ++tile) {
        playerTiles += tile->tileToString();
    }
    return playerTiles;
}

void Player::deleteTile(Tile tileToRemove){
    myTiles_.erase(std::remove(myTiles_.begin(), myTiles_.end(), tileToRemove), myTiles_.end());
}

bool Player::operator==(const Player playerAtRight) const {
    if(this->getUsername() == playerAtRight.getUsername() and this->getPassword() == playerAtRight.getPassword()) {
        return true;
    }        
    return false;   
}

int Player::greatestTileValue(){
    vector<Tile> playerTiles = this->getPlayerTiles();
    int greatestTileValue = 0;
    vector<Tile>::iterator tile;
    for (tile = playerTiles.begin(); tile != playerTiles.end(); ++tile) {
        int tileValue = (*tile).getTileValue();
        if(tileValue > greatestTileValue){
            greatestTileValue = tileValue;
        }
    }
    return greatestTileValue;
}