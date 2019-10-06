#ifndef DOMINO_GAME_H
#define DOMINO_GAME_H

// STL data types
#include <list>
#include <stack>
// Generating random number
#include <cstdlib>
#include <ctime>
// Auxiliar classes
#include "Tile.h"
#include "Player.h"

using std::list;
using std::stack;
class DominoGame {

    private:
        list <Tile> board_;
        stack <Tile> drawPile_;
        void fillAllTiles_(vector <Tile> & allTiles);
        Tile getRandomTile_(vector <Tile> & allTiles);

    public:
        // Fill the draw pile with the 28 domino tiles randomly
        DominoGame();
};

#endif //DOMINO_GAME_H