#include "Client.h"

Client::Client(string serverIpAddress, int serverPortNumber) {
    openClientSocket_();
    fillServerSocketDataStructure_(serverIpAddress, serverPortNumber);
    requestServerConnection_();
    setFileDescriptorStructures_();
}

void Client::openClientSocket_() {
    clientSocketDescriptor_ = socket(AF_INET, SOCK_STREAM, 0);
    if(clientSocketDescriptor_ == -1) {
        cerr << "Could not open client socket" << endl;
        exit(1);
    }
}

void Client::fillServerSocketDataStructure_(string serverIpAddress, int serverPortNumber) {
    serverSocketData_.sin_family = AF_INET;
    serverSocketData_.sin_addr.s_addr = inet_addr(serverIpAddress.c_str());
    serverSocketData_.sin_port = htons(serverPortNumber);
}

void Client::requestServerConnection_() {
    int connectionResult = connect(getClientSocketDescriptor_(), getFormattedServerSocketData_(), getSizeOfServerSocketData_());
    if (connectionResult == -1) {
        cerr << "Connection failure" << endl;
        exit(1);
    }
}

void Client::setFileDescriptorStructures_() {
    FD_ZERO(&readerFileDescriptor_);
    FD_ZERO(&auxiliarFileDescriptor_);
    FD_SET(0, &readerFileDescriptor_);
    FD_SET(clientSocketDescriptor_, &readerFileDescriptor_);
}

void Client::startComunication() {
    bool endComunication = false;

    while (not endComunication) {
        auxiliarFileDescriptor_ = readerFileDescriptor_;
        select(getClientSocketDescriptor_() + 1, &auxiliarFileDescriptor_, NULL, NULL, NULL);
        
        // There is data in the clientSocketFileDescriptor
        if(FD_ISSET(getClientSocketDescriptor_(), &auxiliarFileDescriptor_)) {
            readServerMessage_(endComunication);
        }
        
        // There is data in stdin
        else if (FD_ISSET(0, &auxiliarFileDescriptor_)) {
            sendMessageToServer_(endComunication);
        }
    }

    closeClient();
}

void Client::readServerMessage_(bool &endComunication) {
    memset(messageBuffer_, 0, sizeof(messageBuffer_));
    recv(clientSocketDescriptor_, messageBuffer_, sizeof(messageBuffer_), 0);
            
    cout << messageBuffer_ << endl;
    handleServerErrorMessages_(endComunication);
}

void Client::handleServerErrorMessages_(bool &endComunication) {
    if(strcmp(messageBuffer_, "Too many clients connected\n")) {
        endComunication = true;
    }
}

void Client::sendMessageToServer_(bool &endComunication) {
    memset(messageBuffer_, 0, sizeof(messageBuffer_));
    fgets(messageBuffer_, sizeof(messageBuffer_), stdin);

    handleClientMessage_(endComunication);
    send(clientSocketDescriptor_, messageBuffer_, sizeof(messageBuffer_), 0);
}

void Client::handleClientMessage_(bool &endComunication) {
    if(not strcmp(messageBuffer_, "EXIT\n")) {
        endComunication = true;
    }
}