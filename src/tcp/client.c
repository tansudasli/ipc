#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

#define PORT 9000
#define TEST "Test"
#define BUFFER_SIZE 256

char requestMessage[BUFFER_SIZE] = TEST;
char buffer[BUFFER_SIZE];

/**
 * Basically, It creates a socket(), and connect() to server's master.
 * Then starts receive() and send() data to the client handle created by master.
 *
 * @param argc
 * @param argv = PORT (default=9000)
 * @return
 */
int main(int argc, char const *argv[]) {

    //create the socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);  //domain, type, protocol

    //todo: Replace better error handling w/ perror and exit
    if (clientSocket == -1)
        printf("Socket not created: %d", clientSocket);

    //define address
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = (argv[1] != NULL) ? htons(atoi(argv[1])) : htons(PORT);
    serverAddress.sin_addr.s_addr = INADDR_ANY; //0.0.0.0

    connect(clientSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress));

    //
    recv(clientSocket, buffer, sizeof(buffer), 0);

    printf("received=%s", buffer);

}

