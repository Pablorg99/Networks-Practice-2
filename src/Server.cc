#include "Server.h"

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

Server::Server(int serverPort, int serverCapacity) {
    this->serverCapacity_ = serverCapacity;
    this->serverSocketDescriptor_ = socket (AF_INET, SOCK_STREAM, 0);
    if (this->serverSocketDescriptor_ == -1)
	{
		perror("Error opening server socket\n");
    		exit (1);	
	}
    this->serverSocketData_.sin_family = AF_INET;
    this->serverSocketData_.sin_port = htons(serverPort);
    this->serverSocketData_.sin_addr.s_addr = INADDR_ANY;

    if (bind (this->getServerSocketDescriptor_(), this->getFormattedServerSocketAddress_(), this->getServerSocketDataSize_() == -1))
	{
		perror("Error with bind operation");
		exit(1);
	}

    if(listen(this->serverSocketDescriptor_, this->serverCapacity_) == -1) {
        perror("Error with listen operation");
        exit(1);
    }
}

void Server::clearFDSet() {
    FD_ZERO(&this->ReadSet_);
    FD_SET(this->serverSocketDescriptor_, &this->ReadSet_);

    for (auto clientSocketDescriptor = this->getClients_().begin(); clientSocketDescriptor != this->getClients_().end(); ++clientSocketDescriptor) {
        FD_SET(*clientSocketDescriptor, &this->ReadSet_);
    }
}

void Server::searchForMatch() {
    char buffer[128];
    int connectionSocketDescriptor;
    

    while(1){
        this->clearFDSet();

        select(FD_SETSIZE, &this->ReadSet_, NULL, NULL, NULL);
        for (auto clientSocketDescriptor = this->getClients_().begin(); clientSocketDescriptor != this->getClients_().end(); ++clientSocketDescriptor) {
            if(FD_ISSET(*clientSocketDescriptor, &this->ReadSet_)) {
                if( *clientSocketDescriptor == this->getServerSocketDescriptor_()){
                    if((connectionSocketDescriptor = accept(this->getServerSocketDescriptor_(), this->getFormattedHostInfo_(), this->getSizeOfHost_())) == -1){
                        perror("Error accepting requests");
                    }
            }
        }   
    }

}