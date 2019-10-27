#ifndef DOMINO_GAME_HANDLER_H
#define DOMINO_GAME_HANDLER_H

#define BUFFER_SIZE 128

// socket() and macros
#include <sys/types.h>
#include <sys/socket.h>

#include <regex>

#include <iostream>

#include "DominoGame.h"

class DominoGameHandler {
    
    private:
        char messageBuffer_[BUFFER_SIZE];
        bool matchFinished_;
        DominoGame Game_;
        
        int serverSocketDescriptor_;
        int playerTurnSocketDescriptor_;
        fd_set readerFileDescriptor_;

        void sendMessageToPlayersInGame_(string message);
        void sendMessageToPlayer_(Player *player, string message);
        void setFirstPlayer_();
        void sendHandToPlayers_();
        void manageDrawTile_();
        void passTurn_();
        void endGame_();
        void recreateFileDescriptor_();

    public:
        DominoGameHandler(DominoGame* newGame, int serverSocketDescriptor);
        int playDomino();
        void commandHandler();
};

#endif // DOMINO_GAME_HANDLER_H