#ifndef UDP_NETWORK_HANDLER_HPP
#define UDP_NETWORK_HANDLER_HPP

#include <sys/types.h>      // Provides data types used in system calls
#include <sys/socket.h>     // Provides socket functions and structures
#include <netinet/in.h>     // Provides constants and structures needed for internet domain addresses
#include <unistd.h>         // Provides access to the POSIX operating system API
#include <iostream>         // Provides Input and Output stream classes

// Function prototypes for UDP server and client
int udpServer(int port);
int udpClient(int port);

#endif // UDP_NETWORK_HANDLER_HPP
