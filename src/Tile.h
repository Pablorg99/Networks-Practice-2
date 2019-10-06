#ifndef TILE_H
#define TILE_H

#include <cstdlib>

class Tile{

    private:
        int left_;
        int right_;

    public:
        Tile(int leftValue, int rightValue);
        int getLeft() const {return left_;}
        int getRight() const {return right_;}
        void flipTile();
};

#endif