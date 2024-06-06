#ifndef NETWORK_HANDLER_HPP
#define NETWORK_HANDLER_HPP

#include <iostream>  // For std::cout, std::endl
#include <sys/socket.h>  // For socket functions
#include <netinet/in.h>  // For sockaddr_in
#include <unistd.h>  // For close()

// Function prototypes for TCP server and client
int tcpServer(int port);
int tcpClient(int port);
void tcpConv(int clientSocket);

#endif // NETWORK_HANDLER_HPP
