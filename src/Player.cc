#include "Player.h"
#include <algorithm>

Player::Player(string username, string password) {
    username_ = username;
    password_ = password;
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