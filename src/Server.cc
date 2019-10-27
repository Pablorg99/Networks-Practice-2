#include "Server.h"

Server::Server(int serverPort) {
    openServerSocket_();
    fillServerSocketDataStructure_(serverPort);
    int socketOption = 1;
    setsockopt(serverSocketDescriptor_, SOL_SOCKET, SO_REUSEADDR, &socketOption, sizeof(socketOption));
    assingServerAddressToServerSocket_();
    markServerSocketAsPassiveSocket_();
    numberOfClients_ = 0;
}

void Server::openServerSocket_() {
    serverSocketDescriptor_ = socket (AF_INET, SOCK_STREAM, 0);
    if(serverSocketDescriptor_ == -1) {
        cerr << "Could not open server socket" << endl;
        exit(1);
    }
}

void Server::fillServerSocketDataStructure_(int serverPortNumber) {
    serverSocketData_.sin_family = AF_INET;
    serverSocketData_.sin_addr.s_addr = INADDR_ANY;
    serverSocketData_.sin_port = htons(serverPortNumber);
}

void Server::assingServerAddressToServerSocket_() {
    socklen_t serverSocketDataSize = sizeof(serverSocketData_);
    int bindResult = bind(serverSocketDescriptor_, (struct sockaddr *) &serverSocketData_, serverSocketDataSize);
    if (bindResult == -1) {
		cerr << "Error with bind operation" << endl;
		exit(1);
	}
}

void Server::markServerSocketAsPassiveSocket_() {
    int listenResult = listen(serverSocketDescriptor_, MAX_CLIENTS);
    if(listenResult == -1) {
        cerr << "Error with listen operation" << endl;
        exit(1);
    }
}

void Server::recreateFileDescriptor_() {
    FD_ZERO(&readerFileDescriptor_);
    FD_SET(serverSocketDescriptor_, &readerFileDescriptor_);
    FD_SET(0, &readerFileDescriptor_);
    for (auto clientSocketDescriptor = clientsConnected_.begin(); clientSocketDescriptor != clientsConnected_.end(); ++clientSocketDescriptor) {
        FD_SET(*clientSocketDescriptor, &readerFileDescriptor_);
    }
}

void Server::startServer() {

    while(true) {
        recreateFileDescriptor_();
        select(FD_SETSIZE, &readerFileDescriptor_, NULL, NULL, NULL);
        
        for (auto clientSocketDescriptor = clientsConnected_.begin(); clientSocketDescriptor != clientsConnected_.end(); ++clientSocketDescriptor) {
            if (FD_ISSET(*clientSocketDescriptor, &readerFileDescriptor_)) {
                if ((recv(*clientSocketDescriptor, &messageBuffer_, BUFFER_SIZE, 0) > 0)) {
                    clientMessageHandler_(*clientSocketDescriptor);
                } 
            }
        }

        if (FD_ISSET(serverSocketDescriptor_, &readerFileDescriptor_)) {
            handleNewClient_();
        } 

        if(FD_ISSET(0, &readerFileDescriptor_)) {
            fgets(messageBuffer_, BUFFER_SIZE, stdin);
            serverMessageHandler_();
        }

    }
}

void Server::handleNewClient_() {
    newClientSocketDescriptor_ = accept(serverSocketDescriptor_, (struct sockaddr *) &clientSocketData_ , &clientSocketDataSize_);

    if(newClientSocketDescriptor_ == -1) {
        cerr << "Error accepting requests" << endl;
        exit(1);
    }

    else if(numberOfClients_ < MAX_CLIENTS) {
        addClientToServer_();
    }
    
    else {
        sendTooManyClientsMessageToNewClient_();
    }
}

void Server::addClientToServer_() {
    clientsConnected_.push_back(newClientSocketDescriptor_);
    numberOfClients_++;
    sprintf(messageBuffer_, "Welcome To Server. Use <SEARCH-MATCH>\n");
    send(newClientSocketDescriptor_, messageBuffer_, BUFFER_SIZE, 0);
}

void Server::sendTooManyClientsMessageToNewClient_() {
    sprintf(messageBuffer_, "Too many clients connected\n");
    send(newClientSocketDescriptor_, messageBuffer_, BUFFER_SIZE, 0);
    exitClient_(newClientSocketDescriptor_);
}

void Server::exitClient_(int clientSocketDescriptor) {
    sprintf(messageBuffer_, "You are going to exit the server\n");
    send(clientSocketDescriptor, messageBuffer_, BUFFER_SIZE, 0);
    close(clientSocketDescriptor);
}

void Server::clientMessageHandler_(int clientSocketDescriptor) {
    cout << "Client: " << clientSocketDescriptor << " sent: " << messageBuffer_ << endl;
    if(strcmp(messageBuffer_, "EXIT\n") == 0){                               
        exitClient_(clientSocketDescriptor);
    }
    else if(strcmp(messageBuffer_, "SEARCH-MATCH\n") == 0){
        searchMatchForClient_(clientSocketDescriptor);
    }
    else{
        sprintf(messageBuffer_, "Unknown command, try <SEARCH-MATCH> to start a game\n");
        send(clientSocketDescriptor, messageBuffer_, BUFFER_SIZE, 0);
    }
}

void Server::searchMatchForClient_(int clientSocketDescriptor) {
    vector <int> gamePlayers;
    gamePlayers.push_back(clientSocketDescriptor);

    if (playersQueue_.size() > 0) {
        gamePlayers.push_back(playersQueue_.at(0));
        playersQueue_.erase(playersQueue_.begin());
        sprintf(messageBuffer_, "+Starting game...");
        sendMessageBufferToAllPlayers_(gamePlayers);
    }
    else {
        playersQueue_.push_back(clientSocketDescriptor);
        sprintf(messageBuffer_, "+Searching for another player to play...");
        send(clientSocketDescriptor, messageBuffer_, BUFFER_SIZE, 0);
    }
}

void Server::sendMessageBufferToAllPlayers_(vector <int> gamePlayers) {
    for (auto playerReady = gamePlayers.begin(); playerReady != gamePlayers.end(); ++playerReady) {
        send(*playerReady, messageBuffer_, BUFFER_SIZE, 0);
    }
}

void Server::serverMessageHandler_() {
    if (strcmp(messageBuffer_,"EXIT\n") == 0){
        closeServer_();
    }
}

void Server::closeServer_() {
    for (auto clientSocketDescriptor = clientsConnected_.begin(); clientSocketDescriptor != clientsConnected_.end(); ++clientSocketDescriptor){
        send(*clientSocketDescriptor, "Server is closing\n", strlen("Server is closing\n"),0);
        close(*clientSocketDescriptor);
        FD_CLR(*clientSocketDescriptor, &readerFileDescriptor_);
    }
    close(serverSocketDescriptor_);
    exit(-1);
}