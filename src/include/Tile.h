#ifndef TILE_H
#define TILE_H

// STL Data Types
#include <string>
#include <vector>
#include <algorithm>
using std::find;
using std::to_string;
using std::string;
using std::vector;

class Tile {

    private:
        int left_;
        int right_;

    public:
        Tile(int leftValue, int rightValue);
        inline int getLeft() const {return left_;}
        inline int getRight() const {return right_;}
        Tile flippedTile();
        bool operator==(const Tile rightTile) const;
        inline string tileToString() const {return "|" + to_string(left_) + "|" + to_string(right_) + "|";}
        bool compatibleTile(int value) const;
        bool findTileInTiles(const vector<Tile> tilesVector,const Tile tileToFind);
        inline int getTileValue() { return left_ + right_;}
};

#endif