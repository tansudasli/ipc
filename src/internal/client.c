#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCKET_NAME "/tmp/dummy"
#define BUFFER_SIZE 256

char buffer[BUFFER_SIZE];

/**
 * Send data to socket one by one, as an integer.
 *
 * @param dataSocket
 */
void processOneByOne(int dataSocket) {
    int i;
    int status;

    //write
    do {
        printf("Enter number to send to server :\n");
        scanf("%d", &i);

        status = write(dataSocket, &i, sizeof(int));
        printf("status=%d\n", status);

        if (status == -1) {
            fprintf(stderr, "Data could not send\n");
            perror("write");
            break;
        }

        printf("$ of bytes sent = %d, the data sent = %d\n", status, i);
    } while (i); //exits if 0 enters, means false

    //read - blocking call
    memset(buffer, 0, BUFFER_SIZE);

    status = read(dataSocket, buffer, BUFFER_SIZE);
    if (status == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }

    printf("Received...%s\n", buffer);
}

/**
 * Basically, It creates a socket(), connect().
 * Then, send() and receive().
 *
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char const *argv[]) {

    //create the socket
    int dataSocket = socket(AF_LOCAL, SOCK_STREAM, 0);
    if (dataSocket == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    printf("Data socket created\n");

    //define the server address, and connect
    //connect is related to server's accept !!
    //non-blocking !!
    struct sockaddr_un serverAddress;
    memset(&serverAddress, 0, sizeof(struct sockaddr_un));

    serverAddress.sun_family = AF_LOCAL;
    strncpy(serverAddress.sun_path, SOCKET_NAME, sizeof(SOCKET_NAME) - 1);

    int status = connect(dataSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress));
    if (status == -1) {
        perror("connect");
        fprintf(stderr, "The server is down\n");
        exit(EXIT_FAILURE);
    }

    printf("Connected to server\n");

    //send and receive(blocking)
    processOneByOne(dataSocket);




    //close
    close(dataSocket);
    printf("Data socket closed..\n");

    exit(EXIT_SUCCESS);

}