#include "Client.h"

int main () {
    Client client("127.0.0.1", 2000);
    client.startComunication();
    return 0;
}