#ifndef PARSER_HPP
#define PHLAR
#include <string>
#include <vector>

class Parser {
public:
    struct CommandOptions {
        const char **execArgs; // exec name and arguments
        std::string eArgs[2];  // Additional arguments
        std::string bArgs;     // Option for 'b' flag
        std::string iArgs;     // Option for 'i' flag
        std::string oArgs;     // Option for 'o' flag
        std::string tArgs;     // Option for 't' flag
        int inSocketfd = -1;   // Socket file descriptor for input redirection
        int outSocketfd = -1;  // Socket file descriptor for output redirection
    };

    CommandOptions options; // Struct to store command options

    Parser(int argc, char *argv[]); // Constructor declaration
    void parseOptions(int argc, char *argv[]); // Method to parse command line options
    void updateInputOutput(int &inputfd, int &output_index, int state);
};

#endif // PARSER_HPP
