#include "Player.h"
#include <algorithm>

Player::Player(string username, string password) {
    username_ = username;
    password_ = password;
}

string Player::getPlayerTilesString(){
    vector<Tile>::iterator it;
    string playerTiles = "";
    for (it = myTiles_.begin(); it != myTiles_.end(); ++it) {
        playerTiles += it->tileToString();
    }
    return playerTiles;
}

void Player::deleteTile(Tile tileToRemove){
    myTiles_.erase(std::remove(myTiles_.begin(), myTiles_.end(), tileToRemove), myTiles_.end());
}