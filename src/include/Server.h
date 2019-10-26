#ifndef SERVER_H
#define SERVER_H

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

// String
#include <string>
using std::string;

// STL Data Types
#include <vector>
using std::vector;
using std::size_t;

#include <iostream>
using std::cout;
using std::endl;

using std::cerr;

class Server {

    private:
        int serverSocketDescriptor_;
        inline int getServerSocketDescriptor_() {return serverSocketDescriptor_;}
        
        int newClientSocketDescriptor_;
        inline int getNewClientSocketDescriptor_() {return newClientSocketDescriptor_;}
        
        struct sockaddr_in serverSocketData_;
        inline struct sockaddr * getFormattedServerSocketData_() {return (struct sockaddr *) &this->serverSocketData_;}
        inline socklen_t getSizeOfServerSocketData_() {return sizeof(serverSocketData_);}
        
        struct sockaddr_in clientSocketData_;
        inline struct sockaddr * getFormattedClientSocketData_() {return (struct sockaddr *) &clientSocketData_;}
        inline socklen_t * getSizeOfClientSocketData_(){return (socklen_t *) sizeof(this->clientSocketData_);}
                
        int numberOfClients_;
        inline int getNumberOfClients_() {return numberOfClients_;}
        
        char messageBuffer_[128];
        char messageIdentifier_[256];
        
        vector <int> Clients_;
        inline vector <int> getClients_() {return Clients_;}
        
        fd_set readerFileDescriptor_;
        inline fd_set * getReaderFileDescriptor_() {return &readerFileDescriptor_;}

        fd_set auxiliarFileDescriptor_;
        inline fd_set * getAuxiliarFileDescriptor_() {return &auxiliarFileDescriptor_;}
        

        void openServerSocket_();
        void fillServerSocketDataStructure_(int serverPortNumber);
        void assingServerAddressToServerSocket_();
        void markServerSocketAsPassiveSocket_();
        void setFileDescriptorStructures_();
        
        void handleNewClient_();
        void addClientToServer_();
        void sendTooManyClientsMessageToNewClient_();

    public:
        Server(int serverPort);
        void clearFDSet();
        void serverMessageHandler();
        void clientMessageHandler(int socketID);
        void searchForMatch();
        void exitClient(int socketID, fd_set * readerFileDescriptor_, int numberOfClients , vector <int> Clients);
        void closeServer_();
};   


#endif // SERVER_H 