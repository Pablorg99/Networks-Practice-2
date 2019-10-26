#include "Client.h"

Client::Client(string serverIpAddress, int serverPortNumber) {
    openClientSocket_();
    fillServerSocketAddressStructure_();
}

void Client::openClientSocket_() {
    clientSocketDescriptor_ = socket(AF_INET, SOCK_STREAM, 0);
    if(clientSocketDescriptor_ == -1) {
        throw "Could not open client socket";
    }
}