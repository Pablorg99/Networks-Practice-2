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
        Player firstPlayer_;
        Player secondPlayer_;

        void dealTiles_();
        void fillDrawPile_();

    public:
        DominoGame(Player firstPlayer, Player secondPlayer);
        inline vector <Tile> getDrawPile() const {return drawPile_}
        Tile getRandomTile();
};

#endif //DOMINO_GAME_H