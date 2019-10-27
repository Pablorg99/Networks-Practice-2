#include "Client.h"

Client::Client(string serverIpAddress, int serverPortNumber) {
    openClientSocket_();
    fillServerSocketDataStructure_(serverIpAddress, serverPortNumber);
    requestServerConnection_();
    endComunication_ = false;
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
    socklen_t serverSocketDataSize;
    serverSocketDataSize = sizeof(serverSocketData_);
    int connectionResult = connect(clientSocketDescriptor_, (struct sockaddr *) &serverSocketData_, serverSocketDataSize);
    if (connectionResult == -1) {
        cerr << "Connection failure" << endl;
        exit(1);
    }
}

void Client::setFileDescriptorStructures_() {
    FD_ZERO(&readerFileDescriptor_);
    
    FD_SET(0, &readerFileDescriptor_);
    FD_SET(clientSocketDescriptor_, &readerFileDescriptor_);
}

void Client::startComunication() {

    while (not endComunication_) {
        setFileDescriptorStructures_();
        select(clientSocketDescriptor_ + 1, &readerFileDescriptor_, NULL, NULL, NULL);
        
        // There is data in the clientSocketFileDescriptor
        if(FD_ISSET(clientSocketDescriptor_, &readerFileDescriptor_)) {
            readServerMessage_();
        }
        
        // There is data in stdin
        else if (FD_ISSET(0, &readerFileDescriptor_)) {
            sendMessageToServer_();
        }
    }

    closeClient();
}

void Client::readServerMessage_() {
    memset(messageBuffer_, 0, sizeof(messageBuffer_));
    recv(clientSocketDescriptor_, messageBuffer_, sizeof(messageBuffer_), 0);
            
    cout << messageBuffer_ << endl;
    handleServerErrorMessages_();
}

void Client::handleServerErrorMessages_() {
    if(strcmp(messageBuffer_, "Too many clients connected\n") == 0) {
        endComunication_ = true;
    }
}

void Client::sendMessageToServer_() {
    memset(messageBuffer_, 0, sizeof(messageBuffer_));
    fgets(messageBuffer_, sizeof(messageBuffer_), stdin);

    handleClientMessage_();
    send(clientSocketDescriptor_, messageBuffer_, sizeof(messageBuffer_), 0);
}

void Client::handleClientMessage_() {
    if(not strcmp(messageBuffer_, "EXIT\n")) {
        endComunication_ = true;
    }
}