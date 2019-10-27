#include "DominoGameHandler.h"

#include "Server.h"

DominoGameHandler::DominoGameHandler(DominoGame* newGame, int serverSocketDescriptor): Game_(*newGame) {
    serverSocketDescriptor_ = serverSocketDescriptor;
}

void DominoGameHandler::sendMessageToPlayersInGame_(string message) {
    int firstPlayer = Game_.getFirstPlayer()->getPlayerSocketDescriptor();
    int secondPlayer = Game_.getSecondPlayer()->getPlayerSocketDescriptor();
    sprintf(messageBuffer_, message.c_str());
    send(firstPlayer, messageBuffer_, BUFFER_SIZE, 0);
    send(secondPlayer, messageBuffer_, BUFFER_SIZE, 0);
}

void DominoGameHandler::recreateFileDescriptor_() {
    FD_ZERO(&readerFileDescriptor_);
    FD_SET(serverSocketDescriptor_, &readerFileDescriptor_);
    FD_SET(playerTurnSocketDescriptor_, &readerFileDescriptor_);
}

void DominoGameHandler::sendHandToPlayers_() {
    string firstPlayerHand = Game_.getFirstPlayer()->getPlayerTilesString();
    string secondPlayerHand = Game_.getSecondPlayer()->getPlayerTilesString();
    sendMessageToPlayer_(Game_.getFirstPlayer(), "YOUR HAND: " + firstPlayerHand + "\n");
    sendMessageToPlayer_(Game_.getSecondPlayer(), "YOUR HAND: " + secondPlayerHand + "\n");
}

void DominoGameHandler::sendMessageToPlayer_(Player *player, string message) {
    sprintf(messageBuffer_, message.c_str());
    send(player->getPlayerSocketDescriptor(), messageBuffer_, BUFFER_SIZE, 0);
}

int DominoGameHandler::playDomino(){
    sendMessageToPlayersInGame_("The game has started!");
    Game_.dealTiles();
    setFirstPlayer_();

    matchFinished_ = false;

    while( ! matchFinished_){
        sendMessageToPlayersInGame_("TABLERO: " + Game_.getBoardString() + "\n");
        sendHandToPlayers_();
        recreateFileDescriptor_();

        select(FD_SETSIZE, &readerFileDescriptor_, NULL, NULL, NULL);

        if(FD_ISSET(playerTurnSocketDescriptor_, &readerFileDescriptor_)) {
            if((recv(playerTurnSocketDescriptor_, &messageBuffer_, BUFFER_SIZE, 0) > 0)) {
                commandHandler();
            }
        }        
    }
    
    return 1;
}

void DominoGameHandler::setFirstPlayer_() {
    playerTurnSocketDescriptor_ = Game_.firstPlayerToPlay().getPlayerSocketDescriptor();
    sprintf(messageBuffer_, "You have to start\n");
    send(playerTurnSocketDescriptor_, messageBuffer_, BUFFER_SIZE, 0);
}

void DominoGameHandler::commandHandler() {
    std::cout << "Player: " << playerTurnSocketDescriptor_ << " (SD) sent: " << messageBuffer_;
    
    if (std::regex_match(messageBuffer_, std::regex("PUT-TILE \\|[0-6]\\|[0-6]\\|,(left|right)\n"))) {
        std::cmatch RegexMatches;
        std::regex_search(messageBuffer_, RegexMatches, std::regex("\\|([0-6])\\|([0-6])\\|,(left|right)"));
        Tile tile(atoi(RegexMatches.str(1).c_str()), atoi(RegexMatches.str(2).c_str()));
        if(Game_.getFirstPlayer()->getTurn()) {
            if(Game_.putTile(Game_.getFirstPlayer(), tile, RegexMatches.str(3).c_str())) {
                sendMessageToPlayer_(Game_.getFirstPlayer(), "Your tile was put correctly\n");
                this->passTurn_();
            }
            else {
                sendMessageToPlayer_(Game_.getFirstPlayer(), "You can't put that tile!\n");
            }
        }
        else {
            if(Game_.putTile(Game_.getSecondPlayer(), tile, RegexMatches.str(3).c_str())) {
                sendMessageToPlayer_(Game_.getSecondPlayer(), "Your tile was put correctly\n");
                this->passTurn_();
            }
            else {
                sendMessageToPlayer_(Game_.getSecondPlayer(), "You can't put that tile!\n");
            }
        }
    }
    
    else if(strcmp(messageBuffer_, "DRAW-TILE\n") == 0) {
        manageDrawTile_();
    }
    else if(strcmp(messageBuffer_, "SURRENDER\n") == 0) {
        endGame_();
    }
    else {
        send(playerTurnSocketDescriptor_, "ERROR: This is not a valid option", BUFFER_SIZE, 0);
    }
}

void DominoGameHandler::manageDrawTile_() {
    if(Game_.getFirstPlayer()->getTurn()) {
        if(Game_.canPutAtLeastOneTile(Game_.getFirstPlayer())) {
            sprintf(messageBuffer_, "You can play at least one tile\n");
            send(Game_.getFirstPlayer()->getPlayerSocketDescriptor(), messageBuffer_, BUFFER_SIZE, 0);
        }
        else {
            Game_.getFirstPlayer()->addTile(Game_.drawRandomTile());
        }
    }
    else {
        if(Game_.canPutAtLeastOneTile(Game_.getSecondPlayer())){
            sprintf(messageBuffer_, "You can play at least one tile\n");
            send(Game_.getFirstPlayer()->getPlayerSocketDescriptor(), messageBuffer_, BUFFER_SIZE, 0);
        }
        else {
            Game_.getSecondPlayer()->addTile(Game_.drawRandomTile());
        }
    }
    this->passTurn_();
}

void DominoGameHandler::passTurn_() {
    Game_.passTurn();
    if(Game_.getFirstPlayer()->getTurn()) {
        playerTurnSocketDescriptor_ = Game_.getFirstPlayer()->getPlayerSocketDescriptor();
        sprintf(messageBuffer_, "Your turn has finished\n");
        send(Game_.getSecondPlayer()->getPlayerSocketDescriptor(), messageBuffer_, BUFFER_SIZE, 0);
        sprintf(messageBuffer_, "It's your turn\n");
        send(Game_.getFirstPlayer()->getPlayerSocketDescriptor(), messageBuffer_, BUFFER_SIZE, 0);
    }
    else{
        playerTurnSocketDescriptor_ = Game_.getSecondPlayer()->getPlayerSocketDescriptor();
        sprintf(messageBuffer_, "Your turn has finished\n");
        send(Game_.getFirstPlayer()->getPlayerSocketDescriptor(), messageBuffer_, BUFFER_SIZE, 0);
        sprintf(messageBuffer_, "It's your turn\n");
        send(Game_.getSecondPlayer()->getPlayerSocketDescriptor(), messageBuffer_, BUFFER_SIZE, 0);
    }
}

void DominoGameHandler::endGame_() {
    sendMessageToPlayersInGame_("Game has ended");
    vector <int> playersToQueue = { Game_.getFirstPlayer()->getPlayerSocketDescriptor(), Game_.getSecondPlayer()->getPlayerSocketDescriptor()};

    Server Server(1);
    Server.addClientsToServer(playersToQueue);
    matchFinished_ = true;
    playDomino();
}