#ifndef DOMINO_GAME_H
#define DOMINO_GAME_H

// STL data types
#include <list>
using std::list;
#include <vector>
using std::vector;
// Generating random number
#include <cstdlib>
#include <ctime>
// Auxiliar classes
#include "Player.h"
#include "Tile.h"
#include "DominoGame.h"

class DominoGame {

    private:
        list <Tile> board_;
        vector <Tile> drawPile_;
        int tilesLeftInPile_;
        Player firstPlayer;
        Player secondPlayer;

        void dealTiles_();
        void fillDrawPile_();

    public:
        DominoGame(); // Fill the draw pile with the 28 domino tiles
        Tile getRandomTile();
};

#endif //DOMINO_GAME_H