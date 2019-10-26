#include "Server.h"

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

#define MAX_CLIENTS 30

Server::Server(int serverPort) {
    openServerSocket_();
    fillServerSocketDataStructure_(serverPort);
    assingServerAddressToServerSocket_();
    markServerSocketAsPassiveSocket_();
    setFileDescriptorStructures_();
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
    int bindResult = bind(getServerSocketDescriptor_(), getFormattedServerSocketData_(), getSizeOfServerSocketData_());
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

void Server::setFileDescriptorStructures_() {
    FD_ZERO(&readerFileDescriptor_);
    FD_ZERO(&auxiliarFileDescriptor_);
    FD_SET(0, &readerFileDescriptor_);
}

void Server::handleNewClient_() {

    newClientSocketDescriptor_ = accept(getServerSocketDescriptor_(), getFormattedClientSocketData_(), getSizeOfClientSocketData_());

    if(getNewClientSocketDescriptor_() == -1) {
        cerr << "Error accepting requests" << endl;
        exit(1);
    }

    else if(getNumberOfClients_() < MAX_CLIENTS) {
        addClientToServer_();
    }
    
    else {
        sendTooManyClientsMessageToNewClient_();
    }
}

void Server::addClientToServer_() {
    getClients_().push_back(getNewClientSocketDescriptor_());
    numberOfClients_++;
    FD_SET(getNewClientSocketDescriptor_(), getReaderFileDescriptor_());
    send(getNewClientSocketDescriptor_(), "Welcome to Server\n", strlen("Welcome to Server\n"), 0);
}

void Server::sendTooManyClientsMessageToNewClient_() {
    FD_SET(getNewClientSocketDescriptor_(), getReaderFileDescriptor_());
    send(getNewClientSocketDescriptor_(), "Too many clients connected\n", strlen("Too many clients connected\n"), 0);
}

void Server::searchForMatch() {

    while(true) {
        auxiliarFileDescriptor_ = readerFileDescriptor_;
        select(FD_SETSIZE, getAuxiliarFileDescriptor_(), NULL, NULL, NULL);

        if (FD_ISSET(getServerSocketDescriptor_(), getReaderFileDescriptor_())) {
            handleNewClient_();
        }    

        for (auto clientSocketDescriptor = getClients_().begin(); clientSocketDescriptor != getClients_().end(); ++clientSocketDescriptor) {
            if (FD_ISSET(*clientSocketDescriptor, getReaderFileDescriptor_())) {
                if ((recv(*clientSocketDescriptor, &messageBuffer_, 128, 0) > 0)) {
                    clientMessageHandler(*clientSocketDescriptor);
                } 
            }
        }
    }
}

void Server::startGame(){
    vector <int> gamePlayers;
    gamePlayers.push_back(clientSocketDescriptor);

    if (this->getPlayersQueue_().size() > 0){
        gamePlayers.push_back(this->getPlayersQueue_().at(0));
        playersQueue_.erase(this->getPlayersQueue_.begin() + 0);
    }
}

void Server::serverMessageHandler(){
    memset(messageBuffer_, 0, sizeof(messageBuffer_));
    fgets(messageBuffer_, sizeof(messageBuffer_),stdin);
    if (strcmp(messageBuffer_,"EXIT\n") == 0){
        this->closeServer_();
    }
    // Add server to clients messages

    
}

void Server::closeServer_(){
    for (auto clientSocketDescriptor = Clients_.begin(); clientSocketDescriptor != Clients_.end(); ++clientSocketDescriptor){
        send(*clientSocketDescriptor, "Server is closing\n", strlen("Server is closing\n"),0);
        close(*clientSocketDescriptor);
        FD_CLR(*clientSocketDescriptor, getReaderFileDescriptor_());
    }
    close(serverSocketDescriptor_);
    exit(-1);
}

void Server::clientMessageHandler(int clientSocketDescriptor){
    cout << "Client: " << clientSocketDescriptor << "sent: " << messageBuffer_ << endl;
    if(strcmp(messageBuffer_, "EXIT\n") == 0){                               
        exitClient(clientSocketDescriptor);
    }
    
    else if(strcmp(messageBuffer_, "INICIAR PARTIDA\n") == 0){
        this->startMatch(clientSocketDescriptor);
    }

    else{
        sprintf(messageIdentifier_, "%d: %s", socketID, messageBuffer_);
        memset(messageBuffer_, 0, sizeof(messageBuffer_));
        strcpy(messageBuffer_,messageIdentifier_);
        
        for (auto clientSocketDescriptor = Clients_.begin(); clientSocketDescriptor != Clients_.end(); ++clientSocketDescriptor){
            if(*clientSocketDescriptor != socketID){
                send(*clientSocketDescriptor,messageBuffer_,strlen(messageBuffer_),0);        
            }
        }
    }
}

void Server::exitClient(int clientSocketDescriptor){
    send(clientSocketDescriptor, "Your exit request has been received\n", strlen("Your exit request has been received\n"),0);
    close(clientSocketDescriptor);
}