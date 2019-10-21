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

class DominoGame {

    private:
        list <Tile> board_;
        vector <Tile> drawPile_;
        int tilesLeftInPile_;
        Player *firstPlayer_;
        Player *secondPlayer_;

        void dealTiles_();
        void fillDrawPile_();

    public:
        DominoGame(Player *firstPlayer, Player *secondPlayer);
        inline vector <Tile> getDrawPile() const {return drawPile_;}
        inline int getTilesLeftInPile() const {return tilesLeftInPile_;}
        inline list<Tile> getBoardTiles() const {return board_;}
        Tile getRandomTile();
        bool checkPutAnyTile(Player *player, string boardSide);
        bool checkPutTile(Player *player, Tile tile, string boardSide);
        void putTile(Player *player, Tile tile, string boardSide);
};

#endif //DOMINO_GAME_H