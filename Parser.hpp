#ifndef PARSER_HPP
#define PARSER_HPP
#include <string>
#include <vector>
#include <iostream>
#include <unistd.h>
#include <sstream>
#include <iterator>
#include <cstring>
#include <cstdlib>

class Parser {
public:

        const char **execArgs; // exec name and arguments
        std::string eArgs[2];  // Additional arguments
        std::string bArgs;     // Option for 'b' flag
        std::string iArgs;     // Option for 'i' flag
        std::string oArgs;     // Option for 'o' flag
        std::string tArgs;     // Option for 't' flag
        int inSocketfd = STDIN_FILENO ;   // Socket file descriptor for input redirection
        int outSocketfd = STDOUT_FILENO;  // Socket file descriptor for output redirection


    Parser(int argc, char *argv[]); // Constructor declaration
    void parseOptions(int argc, char *argv[]); // Method to parse command line options
    void makeServerByFlag(int &outputfd,int port); // Method to make a server by flag
    void makeClientByFlag(int &inputfd,int port); // Method to make a client by flag
    int extractNumbers(const std::string& input); // Method to extract numbers from a string

};

#endif // PARSER_HPP
