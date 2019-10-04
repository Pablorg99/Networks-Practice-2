#ifndef DOMINO_GAME_H
#define DOMINO_GAME_H

#include <list>
#include <stack>
#include "Tile.h"
#include "Player.h"

using std::list;
using std::stack;
class DominoGame {
    private:
        list <Tile> board_;
        stack <Tile> drawPile_;
    public:
        DominoGame();
};

#endif //DOMINO_GAME_H