#ifndef TILE_H
#define TILE_H

#include <cstdlib>

class Tile{

    private:
        int left_;
        int right_;

    public:
        int getLeft() const {return left_;}
        int getRight() const {return right_;}
        void setTile(const int leftValue, const int rightValue);
        void flipTile();
        Tile();
};

#endif