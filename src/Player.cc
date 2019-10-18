#include "Player.h"

Player::Player(string username, string password) {
    username_ = username;
    password_ = password;
}

string Player::getPlayerTilesString(){
    vector<Tile>::iterator it;
    for (it = myTiles_.begin(); it != myTiles_.end(); ++it) {
        string playerTiles = "";
        playerTiles += it->tileToString();
    }
}