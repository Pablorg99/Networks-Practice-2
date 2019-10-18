#include "Player.h"

string Player::getPlayerTilesString(){
    vector<Tile>::iterator it;
    for (it = myTiles_.begin(); it != myTiles_.end(); ++it) {
        string playerTiles = "";
        playerTiles += it->tileToString();
    }
}