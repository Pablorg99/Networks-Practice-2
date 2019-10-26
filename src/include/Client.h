#ifndef CLIENT_H
#define CLIENT_H

// socket function and parameters
#include <sys/types.h>
#include <sys/socket.h>

#include <string>
using std::string;

class Client {

    private:
        int clientSocketDescriptor_;
        struct sockaddr_in serverSocketName_;

        void openClientSocket_();
    public:
        Client(string serverIpAddress, int serverPortNumber);
};   


#endif // CLIENT_H