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
int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
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
// sockaddr_in: It is the data type that is used to store the address of the socket.
// htons(): This function is used to convert the unsigned int from machine byte order to network byte order.
// INADDR_ANY: It is used when we don’t want to bind our socket to any particular IP and instead make it listen to all the available IPs.
sockaddr_in serverAddress;
serverAddress.sin_family = AF_INET;
serverAddress.sin_port = htons(port);
serverAddress.sin_addr.s_addr = htonl(INADDR_ANY); // non specific IP address

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

int clientSocket = accept(serverSocket, nullptr, nullptr); //nullpointer is ok becuase the address is always localhost address
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
//init socket
int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

//fill in the server address
sockaddr_in serverAddress;
serverAddress.sin_family = AF_INET;
serverAddress.sin_port = htons(port);
serverAddress.sin_addr.s_addr = INADDR_ANY; // non specific IP address

//connect to the server
if(connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0){
    // handle connection failure
    std::cout << "Error connecting to server" << std::endl;
    perror("connect");
    close(clientSocket);
    return -1;
}
cout << "Connected to server" << endl;


return clientSocket;
}


// //tcp client send mesages to server
// void tcpConv(int clientSocket){
//     char buffer[1024];
//     int n;
//     //fork a child process to reads and the parent process writes 
//     if(fork() == 0){
//         while(1){
//             bzero(buffer, 1024);
//             n = read(clientSocket, buffer, 1024);
//             if(n < 0){
//                 std::cout << "Server is down / Error reading from socket" << std::endl;
//                 perror("read");
//                 close(clientSocket);
//                 exit(1);
//             }
//             std::cout << "Server: " << buffer << std::endl;
//         }
//     }else{
//         while(1){
//             bzero(buffer, 1024);
//             fgets(buffer, 1024, stdin);
//             n = write(clientSocket, buffer, strlen(buffer));
//             if(n < 0){
//                 std::cout << "Server is down / Error writing to socket" << std::endl;
//                 perror("write");
//                 close(clientSocket);
//                 exit(1);
//             }
//         }
//     }
// }


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


