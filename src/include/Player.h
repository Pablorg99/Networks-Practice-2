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
        vector <Tile> myTiles_;

    public:
        Player(string username, string password);
        inline void addTile(Tile newTile) {myTiles_.push_back(newTile);}
        void deleteTile(Tile tileToRemove);
        inline vector <Tile> getPlayerTiles() {return myTiles_;}
        string getPlayerTilesString();
        inline string getUsername() const {return username_;}
        inline string getPassword() const {return password_;}
        bool operator==(const Player playerAtRight) const;
};

#endif