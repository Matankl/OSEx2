// this class is used to parse the argv[] array and get the correct values for the options
// it hes a method that uses getopt() to get the correct values for the options and store them in the correct variables
// it also has a method that returns the correct port if needed
// it also has a method that returns the exec_name and the arguments if needed

#include <string>
// #include <cstring>
#include <string.h>
#include <cstdlib>
#include <vector>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <iterator>
#include "Parser.hpp"
#include "TCPhandler.hpp"


using namespace std;



    // Constructor
    Parser::Parser(int argc, char *argv[])
    {
        parseOptions(argc, argv); // Parse options on initialization
    }

    // Method to parse command line options
    void Parser::parseOptions(int argc, char *argv[])
    {
        int opt;
        // Use getopt to parse options with arguments
        while ((opt = getopt(argc, argv, "e:i:o:b:t:")) != -1)
        {
            switch (opt)
            {
            case 'e':
            {
                cout << "flag \"e\" found: " << optarg << endl;
                // parse by spaces and store in eArgs
                istringstream iss(optarg);                                                        // Create string stream from optarg
                vector<string> tokens{istream_iterator<string>{iss}, istream_iterator<string>{}}; // Tokenize by spaces
                
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
                cout << "flag \"i\" found: " << optarg << endl;
                iArgs = optarg; // Set argument
                break;
            case 'o':
                cout << "flag \"o\" found: " << optarg << endl;
                oArgs = optarg; // Set argument
                break;
            case 'b':
                cout << "flag \"b\" found: " << optarg << endl;
                bArgs = optarg; // Set argument
                break;

            default:
                cout << "No flags found... are you trying to trick me?!?!" << endl;
                exit(EXIT_FAILURE);
            }
        }
    }

    // this method updats the input and the output by the values of the flegs
    //state 0 is for the b flag (both i and o flags are set to the same value)
    //state 1 is for the i flag (input flag)
    //state 2 is for the o flag (output flag)
    void Parser::updateInputOutput(int &inputfd, int &outputfd, int state){
        string protocolPort = "";
        int temp_fd = -1;
        //set the protocolPort to the correct value
        switch (state){
            case 0:
                protocolPort = bArgs;
                break;
            case 1:
                protocolPort = iArgs;
                break;
            case 2:
                protocolPort = oArgs;
                break;
        }
        // --------- make the right server/client call here ------------
        if (protocolPort.compare(0, 4, "TCPS") == 0) {
            cout << "i got TCPS for state" << state << endl;
            //open server socket 
            temp_fd = tcpServer(stoi(protocolPort.substr(4)));
        }
        else if (protocolPort.compare(0, 4, "TCPC") == 0) {
            cout << "i got TCPC for state" << state << endl;
            temp_fd = tcpClient(stoi(protocolPort.substr(14)));  // Assuming that the port starts right after "TCPC"
        }



        // --------- set the right input/output file descriptor here ------------
    cout << "DEBUG PRINT: DELETE LATER! this is the point before updating the input and the output in the method" << endl;


        if (state == 0){
            inputfd = temp_fd;
            outputfd = temp_fd;
        }
        else if (state == 1){
            inputfd = temp_fd;
        }
        else if (state == 2){
            outputfd = temp_fd;
        }
    }