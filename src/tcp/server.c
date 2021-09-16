#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
//#include <unistd.h>

#define PORT 9000
#define MAX_QUEUE_LENGTH 2
#define WELCOME "Welcome"
#define BUFFER_SIZE 256

char serverMessage[BUFFER_SIZE] = WELCOME;

/**
 * Basically, It creates a socket(), bind(), listen(), and accept().
 * Then starts receive() and send() data to the client.
 *
 * @param argc
 * @param argv = PORT (default=9000), MAX_QUEUE_LENGTH (default=2),  ...
 * @return
 */
int main(int argc, char const *argv[]) {

    //create the socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);  //domain, type, protocol

    //todo: Replace better error handling w/ perror and exit
    if (serverSocket == -1)
        printf("Server Socket not created: %d", serverSocket);

    //define and bind the server address
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = (argv[1] != NULL) ? htons(atoi(argv[1])) : htons(PORT);
    serverAddress.sin_addr.s_addr = INADDR_ANY; //0.0.0.0

    int status = bind(serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress));

    if (status == -1)
        printf("Bind is not successful: %d", status);

    //todo: set MAX_QUEUE_LENGTH if argv[2] is valid
    //listen
    status = listen(serverSocket, MAX_QUEUE_LENGTH);

    if (status == -1)
        printf("Listen is not successful: %d, max connection length= %d", status, MAX_QUEUE_LENGTH);

    //accept
    int clientSocket = accept(serverSocket, NULL, NULL);

    if (clientSocket == -1)
        printf("Client Socket is not created: %d", clientSocket);

    //send 1st message
    status = send(clientSocket, serverMessage, sizeof(serverMessage), 0);

    if (status == -1)
        printf("Send is not successful: %d", status);

    //close(serverSocket);
}