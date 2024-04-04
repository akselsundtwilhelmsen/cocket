#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <arpa/inet.h>


int runReceiver(unsigned int port)
{

    char serverMessage[256] = "Receiver reached!!!";

    // Create socket
    int receiverSocket = socket(AF_INET, SOCK_STREAM, 0);

    // Receiver address
    struct sockaddr_in receiverAddress;
    receiverAddress.sin_family = AF_INET;
    receiverAddress.sin_port = htons(port);
    receiverAddress.sin_addr.s_addr = INADDR_ANY;

    if (bind(receiverSocket,
             (struct sockaddr*) &receiverAddress,
             sizeof(receiverAddress)) != 0)
    {
        return 1;
    }

    printf("Ready to receive!\n");

    listen(receiverSocket, 1);
    while (1)
    {
        int senderSocket = accept(receiverSocket, NULL, NULL);
        send(senderSocket, serverMessage, sizeof(serverMessage), 0);
    }
    return 0;
}

int main(int argc, char* argv[])
{
    unsigned int receiverPort = 5000;
    runReceiver(receiverPort);
}

