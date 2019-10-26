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
    FD_SET(serverSocketDescriptor_, &readerFileDescriptor_);
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

    int socketID;
    int receivedMessages;
    
    while(1){

        auxiliarFileDescriptor_ = readerFileDescriptor_;

        int exit = select(FD_SETSIZE, &this->readerFileDescriptor_, NULL, NULL, NULL);

        if ( exit > 0 ){
            for(socketID = 0; socketID < FD_SETSIZE; socketID++){
                if(FD_ISSET(socketID, &auxiliarFileDescriptor_)){
                    if(socketID == serverSocketDescriptor_){
                        this->handleNewClient_();
                    }
                    else if(socketID == 0){
                        this->serverMessageHandler();
                    }
                    else{
                        memset(messageBuffer_, 0, sizeof(messageBuffer_));
                            
                        receivedMessages = recv(socketID,messageBuffer_,sizeof(messageBuffer_),0);
                        if (receivedMessages > 0){
                            clientMessageHandler(socketID);
                        }
                        if(receivedMessages == 0){
                            printf("The client %d, left the game\n", socketID);
                            exitClient(socketID, getReaderFileDescriptor_(), this->getNumberOfClients_(), this->getClients_());
                        }
                    }
                }
            }
        }
    }
    close(serverSocketDescriptor_);
    exit(-1);
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

void Server::clientMessageHandler(int socketID){
    if(strcmp(messageBuffer_,"EXIT\n") == 0){                               
        cout << "The client %d, left the game" << endl;
        exitClient(socketID, getReaderFileDescriptor_(), this->getNumberOfClients_(), this->getClients_());
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

void Server::exitClient(int socketID, fd_set * readerFileDescriptor_, int numberOfClients , vector <int> Clients){
    close(socketID);
    FD_CLR(socketID,readerFileDescriptor_);
    
    for (auto clientSocketDescriptor = Clients_.begin(); clientSocketDescriptor != Clients_.end(); ++clientSocketDescriptor) {
        if(*clientSocketDescriptor != socketID){
            break;     
        }
    }
    for (auto clientSocketDescriptor = Clients_.begin(); clientSocketDescriptor != Clients_.end(); ++clientSocketDescriptor) {
        clientSocketDescriptor = clientSocketDescriptor++;
    }
    this->numberOfClients_--;
    
    memset(messageBuffer_, 0, sizeof(messageBuffer_));
    sprintf(messageBuffer_, "Desconexión del cliente: %d\n", socketID)  ;
    
    for (auto clientSocketDescriptor = Clients_.begin(); clientSocketDescriptor != Clients_.end(); ++clientSocketDescriptor) {
        if(*clientSocketDescriptor != socketID){
            send(*clientSocketDescriptor, messageBuffer_, strlen(messageBuffer_), 0);     
        }
    }
}