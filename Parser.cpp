#include <string>
#include <cstring>
#include <string.h>
#include <cstdlib>
#include <vector>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <iterator>
#include "Parser.hpp"
#include "TCPhandler.hpp"
// #include "UDPhandler.hpp"

// Constructor
Parser::Parser(int argc, char *argv[]){
    parseOptions(argc, argv); // Parse options on initialization
}

// Method to parse command line options
void Parser::parseOptions(int argc, char *argv[]){
    int opt;
    // Use getopt to parse options with arguments
    while ((opt = getopt(argc, argv, "e:i:o:b:t:")) != -1)
    {
        switch (opt)
        {
        case 'e':
        {
            std::cout << "flag \"e\" found: " << optarg << std::endl;
            // parse by spaces and store in eArgs
            std::istringstream iss(optarg);                                                        // Create string stream from optarg
            std::vector<std::string> tokens{std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{}}; // Tokenize by spaces
            
            execArgs = new const char *[tokens.size() + 1];                           // +1 for null termination
            for (size_t i = 0; i < tokens.size(); ++i)
            {
                execArgs[i] = tokens[i].c_str();
            }
            execArgs[tokens.size()] = nullptr; // Null-terminate the array
                                                       // Set argument
            break;
        }
        case 'i':
            std::cout << "flag \"i\" found: " << optarg << std::endl;
            iArgs = optarg; // Set argument
            break;
        case 'o':
            std::cout << "flag \"o\" found: " << optarg << std::endl;
            oArgs = optarg; // Set argument
            break;
        case 'b':
            std::cout << "flag \"b\" found: " << optarg << std::endl;
            bArgs = optarg; // Set argument
            break;

        default:
            std::cout << "No flags found... are you trying to trick me?!?!" << std::endl;
            std::exit(EXIT_FAILURE);
        }
    }
}

// this method updates the input and the output by the values of the flags
void Parser::makeServerByFlag(int &input_fd, int port){
    std::string protocolPort = iArgs;
    int temp_fd = -1;
    if (protocolPort.compare(0, 4, "TCPS") == 0) {
        // open server socket 
        temp_fd = tcpServer(port); 
    }

    input_fd = temp_fd;
}

/*
# generates the client side and if -e flag is set it will get it to send messages to the server
# if flag -e is not set it will just make the client
*/
void Parser::makeClientByFlag(int &output_fd, int port){
    std::cout << "DEBUG PRINT: DELETE LATER! this is the port givan to the client: " << port << std::endl;
    std::string protocolPort = oArgs;
    if (protocolPort.compare(0, 4, "TCPC") == 0) {
        output_fd = tcpClient(port);  // Assuming that the port starts right after "TCPC"
    }

    if(execArgs!= NULL){
    std::cout << "DEBUG PRINT: DELETE LATER! this is if eArg in PARSER" << std::endl;
        tcpConv(output_fd);
    }
}

/*
# this method is used to extract the numbers from a string (port)
*/
int Parser::extractNumbers(const std::string& input) {
    std::string result;
    for (char c : input) {
        if (std::isdigit(c)) {  // Check if the character is a digit
            result += c;
        }
    }
    return std::stoi(result);
}
