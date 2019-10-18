#ifndef TILE_H
#define TILE_H

#include <string>
using std::to_string;
using std::string;

class Tile {

    private:
        int left_;
        int right_;

    public:
        Tile(int leftValue, int rightValue);
        inline int getLeft() const {return left_;}
        inline int getRight() const {return right_;}
        void flipTile();
        inline string tileToString() {return "|" + to_string(left_) + "|" + to_string(right_) + "|";}
};

#endif