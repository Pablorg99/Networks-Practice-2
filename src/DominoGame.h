#ifndef DOMINO_GAME_H
#define DOMINO_GAME_H

// STL data types
#include <list>
#include <vector>
// Generating random number
#include <cstdlib>
#include <ctime>
// Auxiliar classes
#include "Tile.h"
#include "Player.h"

using std::list;
using std::vector;
class DominoGame {

    private:
        list <Tile> board_;
        vector <Tile> drawPile_;
        int tilesLeft_;

    public:
        DominoGame(); // Fill the draw pile with the 28 domino tiles
        Tile getRandomTile();
};

#endif //DOMINO_GAME_H