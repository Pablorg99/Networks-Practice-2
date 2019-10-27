#ifndef PLAYER_H
#define PLAYER_H

// STL data types
#include <vector>
#include <string>
using std::vector;
using std::string;
// Auxiliar classes
#include "Tile.h"

class Player {

    private:
        string username_;
        string password_;
        int playerSocketDescriptor_;
        bool isTurn_;

    public:
        vector <Tile> myTiles_;
        Player(string username, string password, int playerSocketDescriptor);
        inline int getPlayerSocketDescriptor() {return playerSocketDescriptor_;}
        inline void addTile(Tile newTile) {myTiles_.push_back(newTile);}
        inline void setTurnToTrue() {isTurn_ = true;}
        inline void setTurnToFalse() {isTurn_ = false;}
        inline bool getTurn() {return isTurn_;}
        void deleteTile(Tile tileToRemove);
        inline vector <Tile> getPlayerTiles() const {return myTiles_;}
        string getPlayerTilesString();
        inline string getUsername() const {return username_;}
        inline string getPassword() const {return password_;}
        bool operator==(const Player playerAtRight) const;
        int greatestTileValue();
};

#endif