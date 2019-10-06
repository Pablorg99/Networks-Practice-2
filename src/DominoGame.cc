#include "DominoGame.h"
#include <vector>
using std::vector;

DominoGame::DominoGame() {
    vector <Tile> allTiles;
    fillAllTiles_(allTiles);

    Tile tileToAppend(-1,-1);
    int tilesLeft = 28;
    while (tilesLeft > 0) {
        tileToAppend = getRandomTile_(allTiles);
        drawPile_.push(tileToAppend);
    }
}

void DominoGame::fillAllTiles_(vector <Tile> & allTiles) {
    allTiles.push_back(Tile(6,6));
    allTiles.push_back(Tile(6,5));
    allTiles.push_back(Tile(6,4));
    allTiles.push_back(Tile(6,3));
    allTiles.push_back(Tile(6,2));
    allTiles.push_back(Tile(6,1));
    allTiles.push_back(Tile(6,0));
    allTiles.push_back(Tile(5,5));
    allTiles.push_back(Tile(5,4));
    allTiles.push_back(Tile(5,3));
    allTiles.push_back(Tile(5,2));
    allTiles.push_back(Tile(5,1));
    allTiles.push_back(Tile(5,0));
    allTiles.push_back(Tile(4,4));
    allTiles.push_back(Tile(4,3));
    allTiles.push_back(Tile(4,2));
    allTiles.push_back(Tile(4,1));
    allTiles.push_back(Tile(4,0));
    allTiles.push_back(Tile(3,3));
    allTiles.push_back(Tile(3,2));
    allTiles.push_back(Tile(3,1));
    allTiles.push_back(Tile(3,0));
    allTiles.push_back(Tile(2,2));
    allTiles.push_back(Tile(2,1));
    allTiles.push_back(Tile(2,0));
    allTiles.push_back(Tile(1,1));
    allTiles.push_back(Tile(1,0));
    allTiles.push_back(Tile(0,0));
}

Tile DominoGame::getRandomTile_(vector <Tile> & allTiles) {
    Tile auxiliarTile(-1,-1);
    Tile nullTile(-1,-1);
    int tileIndex;
    do {
        tileIndex = rand() % 28;
        auxiliarTile = allTiles[tileIndex];
        if(auxiliarTile != nullTile) {
            allTiles[tileIndex] = nullTile;
        }
    } while (auxiliarTile == nullTile);
    return auxiliarTile;
}