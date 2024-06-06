#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "TCPhandler.hpp"
using namespace std;

// this is a method to handle the TCP server
int tcpServer(int port){
    std::cout << "tcpServer method on the go" << std::endl;
//init socket
int serverSocket, clientSocket;
struct sockaddr_in serverAddress, clientAddress; 
serverSocket = socket(AF_INET, SOCK_STREAM, 0);
if(serverSocket < 0){
    // handle socket creation failure
    std::cout << "Error creating socket (server)" << std::endl;
    perror("socket");
    return -1;
}

//allow the socket to be reused immediately after it is closed
int enable = 1;
if(setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0){
    // handle setsockopt failure
    std::cout << "Error setting socket options" << std::endl;
    perror("setsockopt");
    close(serverSocket);
    return -1;
}

//fill in the server address
serverAddress.sin_family = AF_INET;
serverAddress.sin_port = htons(port);
serverAddress.sin_addr.s_addr = INADDR_ANY; // non specific IP address

//bind the socket to the address
if(bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0){
    // handle binding failure
    std::cout << "Error binding socket (server)" << std::endl;
    perror("bind");
    close(serverSocket);
    return -1;
}
// first arg is the socket file descriptor, second arg is the maximum number of connections that can be waiting while the process is handling a particular connection
if(listen(serverSocket, 1) < 0){
    // handle listening failure
    std::cout << "Error listening on socket" << std::endl;
    perror("listen");
    close(serverSocket);
    return -1;
}

std::cout << "Server listening on port " << port << std::endl;
socklen_t client_addr_size = sizeof(clientAddress);
clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &client_addr_size ); //nullpointer is ok becuase the address is always localhost address
if(clientSocket < 0){
    // handle accepting failure
    std::cout << "Error accepting connection" << std::endl;
    perror("accept");
    close(serverSocket);
    return -1;
}

std::cout << "Connection accepted" << std::endl;

return clientSocket;
}

// this is a method to handle the TCP client
int tcpClient(int port){
// //init socket
// int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

// //fill in the server address
// sockaddr_in serverAddress;
// serverAddress.sin_family = AF_INET;
// serverAddress.sin_port = htons(port);
// serverAddress.sin_addr.s_addr = INADDR_ANY; // non specific IP address

// //connect to the server
// if(connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0){
//     // handle connection failure
//     std::cout << "Error connecting to server" << std::endl;
//     perror("connect");
//     close(clientSocket);
//     return -1;
// }
// cout << "Connected to server" << endl;


// return clientSocket;

    int client_sock;
    struct sockaddr_in server_addr;
    char buffer[1024];

    client_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (client_sock < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (connect(client_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect failed");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Child process: read from server
        while (1) {
            ssize_t bytes_read = read(client_sock, buffer, 1024 - 1);
            if (bytes_read <= 0) {
                break; // Exit loop on read error or server disconnect
            }
            buffer[bytes_read] = '\0';
            printf("Received from server: %s\n", buffer);
        }
        close(client_sock);
        exit(0);
    } else { // Parent process: write to server
        while (1) {
            printf("Enter message (-1 to quit): ");
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline character

            if (strcmp(buffer, "-1") == 0) {
                break; // Exit loop if user enters -1
            }

            write(client_sock, buffer, strlen(buffer));
        }
        close(client_sock);
      

        kill(pid, SIGKILL); // Kill child process reading from server
    }
    return 0;
}

void tcpConv(int clientSocket){
    char buffer[1024];
    int n;
    if(fork() == 0){ // Child process - Reads
        while(1){
            bzero(buffer, 1024);
            n = read(clientSocket, buffer, 1024);
            if(n <= 0){
                cout << "Server is down or connection closed by server" << endl;
                perror("read");
                close(clientSocket);
                exit(1);
            }
            if(strncmp(buffer, "exit", 4) == 0) {
                //send exit message to server
                std:string exit = "exit";
                write(clientSocket, exit.c_str(), exit.length());
                cout << "other side has ended the session." << endl;
                close(clientSocket);
                break; // Exit the loop
            }
            cout << buffer << endl;
        }
        exit(0); // Exit child process
    }else{ // Parent process - Writes
        while(1){
            bzero(buffer, 1024);
            fgets(buffer, 1024, stdin);
           buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline character
            if(strncmp(buffer, "exit", 4) == 0) {
                write(clientSocket, buffer, strlen(buffer));
                cout << "Exiting session." << endl;
                break; // Exit the loop
            }
            n = write(clientSocket, buffer, strlen(buffer));
            if(n < 0){
                cout << "Error writing to socket" << endl;
                perror("write");
                close(clientSocket);
                exit(1);
            }
        }
    }
        close(clientSocket); // Close the socket properly
}


