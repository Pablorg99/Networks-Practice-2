#ifndef CLIENT_H
#define CLIENT_H


#include <sys/types.h>
// socket() and parameters
#include <sys/socket.h>
// sockaddr_in structure
#include <netinet/in.h>
// htons(), inet_addr()
#include <arpa/inet.h>
// close()
#include <unistd.h>
// bzero()
#include <cstring>

#include <string>
using std::string;

#include <iostream>
using std::cout;
using std::endl;

using std::cerr;

class Client {

    private:
        int clientSocketDescriptor_;
        struct sockaddr_in serverSocketData_;
        fd_set readerFileDescriptor_;
        char messageBuffer_[128];
        bool endComunication_;

        void openClientSocket_();
        void fillServerSocketDataStructure_(string serverIpAddress, int serverPortNumber);
        void requestServerConnection_();
        void setFileDescriptorStructures_();

        void readServerMessage_();
        void handleServerErrorMessages_();
        void sendMessageToServer_();
        void handleClientMessage_();

    public:
        Client(string serverIpAddress, int serverPortNumber);
        inline void closeClient() {close(clientSocketDescriptor_);}
        void startComunication();
};   


#endif // CLIENT_H