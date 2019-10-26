#include "Server.h"

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

Server::Server(int serverPort, int serverCapacity){
    this->serverCapacity_ = serverCapacity;
    this->serverSocketDescriptor_ = socket (AF_INET, SOCK_STREAM, 0);
    if (this->serverSocketDescriptor_ == -1)
	{
		perror("Error opening client socket\n");
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

    if(listen(this->serverSocketDescriptor_, this->serverCapacity_) == -1){
        perror("Error with listen operation");
        exit(1);
    }
}