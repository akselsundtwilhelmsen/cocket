#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void sendFile(char* ipAddr, unsigned int port, char* filePath)
{
    // Create socket
    int senderSocket = socket(AF_INET, SOCK_STREAM, 0);

    // Sender address
    struct sockaddr_in receiverAddress;
    receiverAddress.sin_family = AF_INET;
    receiverAddress.sin_port = htons(port);
    receiverAddress.sin_addr.s_addr = inet_addr(ipAddr);

    int conStatus = connect(senderSocket,
                            (struct sockaddr *) &receiverAddress,
                            sizeof(receiverAddress));
    if (conStatus != 0)
    {
        printf("Error making connection.\n");
        return;
    }

    char serverResponse[256];
    recv(senderSocket, &serverResponse, sizeof(serverResponse), 0);
    printf("server Response: %s\n", serverResponse);
    /* close(senderSocket); */
}

int runReceiver(unsigned int port)
{
    char serverMessage[256] = "Receiver reached!!!";

    // Create socket
    int receiverSocket = socket(AF_INET, SOCK_STREAM, 0);

    // Receiver address
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    if (bind(receiverSocket,
             (struct sockaddr*)&serverAddress,
             sizeof(serverAddress)) != 0)
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

/* char[] encrypt(char* bytes[], char* key[]) */
/* { */
/*     return *bytes; */
/* } */

int runSender(void)
{
    while (1)
    {
        char ipAddr[16];
        printf("IP address: ");
        scanf("%15s", ipAddr);
        /* fgets(ipAddr, 16, stdin); */

        unsigned int port;
        printf("Port number: ");
        scanf("%d", &port);

        char filePath[128];
        printf("File to send: ");
        scanf("%127s", filePath);
        /* fgets(filePath, 128, stdin); */

        char key[128];
        printf("Encryption key: ");
        scanf("%127s", key);
        /* fgets(key, 128, stdin); */

        printf("Sending file %s to %s, port %d...\n", filePath, ipAddr, port); // useless
        sendFile(ipAddr, port, filePath);

        scanf("Keep sending? [y/n]");
        char choice;
        scanf("%c", &choice);
        if (choice == 'n' || choice == 'N')
        {
            return 1;
        }

        /* puts("\x1B[2J"); // Clear terminal */
    }
    return 0;
}

int main(int argc, char* argv[])
{
    puts("\x1B[2J"); // Clear terminal 
    printf("Send or Receive? [s/r] ");
    char choice;
    scanf("%c", &choice);
    if (choice == 's' || choice == 'S')
    {
        runSender();
    }
    else if (choice == 'r' || choice == 'R')
    {
        printf("Port number: ");
        unsigned int portNumber;
        scanf("%d", &portNumber);
        runReceiver(portNumber);
    }
}

// TODO:
// multiple tcp streams?
