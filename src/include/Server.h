#ifndef SERVER_H
#define SERVER_H

#include <unistd.h>
// socket function and parameters
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
// STL Data Types
#include <vector>
#include <string>
using std::vector;
using std::size_t;

class Server {

    private:
        int serverSocketDescriptor_;
        int serverCapacity_;
        struct sockaddr_in serverSocketData_;
        struct sockaddr_in hostInfo_;
        socklen_t hostSize_;
        vector<int> Clients_;
        fd_set ReadSet_;
        inline const struct sockaddr * getFormattedServerSocketAddress_() {return (struct sockaddr *) &this->serverSocketData_;}
        inline int getServerSocketDescriptor_() {return serverSocketDescriptor_;}
        inline socklen_t getServerSocketDataSize_() {return sizeof(&this->serverSocketData_);}
        inline vector<int> getClients_(){return Clients_;}
        inline struct sockaddr * getFormattedHostInfo_(){return (struct sockaddr *) &this->hostInfo_;}
        inline socklen_t * getSizeOfHost_(){return (socklen_t *) sizeof(this->hostInfo_);}

    public:
        Server(int serverPort, int serverCapacity);
        void clearFDSet();
        void handleMessage(int clientSocketDescriptor, const char* message);
        void searchForMatch();
};   


#endif // SERVER_H 