#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <arpa/inet.h>


int runSender(char* ip, unsigned int port)
{
    // Create socket
    int senderSocket = socket(AF_INET, SOCK_STREAM, 0);

    // Sender address
    struct sockaddr_in receiverAddress;
    receiverAddress.sin_family = AF_INET;
    receiverAddress.sin_port = htons(port);
    receiverAddress.sin_addr.s_addr = inet_addr(ip);

    int conStatus = connect(senderSocket,
                            (struct sockaddr *) &receiverAddress,
                            sizeof(receiverAddress));
    if (conStatus != 0)
    {
        printf("Error making connection.\n");
        return 1;
    }
    char serverResponse[256];
    recv(senderSocket, &serverResponse, sizeof(serverResponse), 0);
    printf("server Response: %s\n", serverResponse);
    /* close(senderSocket); */
    return 0;
}

int main(int argc, char* argv[])
{
    unsigned int receiverPort = 5000;
    char ip[32] = "127.0.0.1";
    runSender(ip, receiverPort);
}
