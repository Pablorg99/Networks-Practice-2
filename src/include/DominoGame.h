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

        void fillDrawPile_();

    public:
        DominoGame(Player *firstPlayer, Player *secondPlayer);
        inline vector <Tile> getDrawPile() const {return drawPile_;}
        inline int getTilesLeftInPile() const {return tilesLeftInPile_;}
        inline list <Tile> getBoard() const {return board_;}
        string getBoardString() const;
        void dealTiles();
        bool canPutAtLeastOneTile(Player *player);
        Tile drawRandomTile();
        void putTile(Player *player, Tile tile, string boardSide);
        bool canPutTile(const Tile tile);
        inline void addTileAtBack(Tile newTile) {board_.push_back(newTile);}
        inline void addTileAtFront(Tile newTile) {board_.push_front(newTile);}
        bool findTileInTiles(const vector<Tile> tilesVector,const Tile tileToFind);
        Player firstPlayerToPlay();
};

#endif //DOMINO_GAME_H