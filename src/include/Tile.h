#ifndef TILE_H
#define TILE_H

class Tile {

    private:
        int left_;
        int right_;

    public:
        Tile(int leftValue, int rightValue);
        inline int getLeft() const {return left_;}
        inline int getRight() const {return right_;}
        void flipTile();
};

#endif