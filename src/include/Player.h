#ifndef PLAYER_H
#define PLAYER_H

// STL data types
#include <vector>
using std::vector;
// Auxiliar classes
#include "Tile.h"

class Player {

    private:
        vector <Tile> myTiles_;

    public:
        Player();
        inline void addTile(Tile newTile) {myTiles_.push_back(newTile);}
};

#endif