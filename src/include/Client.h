#ifndef CLIENT_H
#define CLIENT_H


#include <sys/types.h>
// socket() and parameters
#include <sys/socket.h>
// sockaddr_in structure
#include <netinet/in.h>
// htons()
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
        fd_set auxiliarFileDescriptor_;
        char messageBuffer_[128];

        inline int getClientSocketDescriptor_() {return clientSocketDescriptor_;}
        inline const struct sockaddr * getFormattedServerSocketData_() {return (struct sockaddr *) &serverSocketData_;}
        inline socklen_t getServerSocketDataSize_() {return sizeof(serverSocketData_);}
        
        void openClientSocket_();
        void fillServerSocketDataStructure_(string serverIpAddress, int serverPortNumber);
        void requestServerConnection_();
        void setFileDescriptorStructures_();

        void readServerMessage_(bool &endComunication);
        void handleServerErrorMessages_(bool &endComunication);
        void sendMessageToServer_(bool &endComunication);
        void handleClientMessage_(bool &endComunication);

    public:
        Client(string serverIpAddress, int serverPortNumber);
        inline void closeClient() {close(getClientSocketDescriptor_());}
        void startComunication();
};   


#endif // CLIENT_H