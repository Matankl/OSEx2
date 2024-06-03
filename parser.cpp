// this class is used to parse the argv[] array and get the correct values for the options
// it hes a method that uses getopt() to get the correct values for the options and store them in the correct variables
// it also has a method that returns the correct port if needed
// it also has a method that returns the exec_name and the arguments if needed

#include <string>
#include <vector>
#include <unistd.h>
#include <iostream>
#include <sstream>

class Parser {
public:
    struct CommandOptions {
        std::string execName;                   // Name of the executable
        std::vector<std::string> execArgs;      // Arguments for the executable
        std::string inputFile;                  // File for input redirection
        std::string outputFile;                 // File for output redirection
        std::string protocol;                   // Network protocol (not fully implemented)
        int port;                               // Network port
        int inSocketfd = -1;                    // Socket file descriptor for input redirection
        int outSocketfd = -1;                   // Socket file descriptor for output redirection
    };

    CommandOptions options;                     // Struct to store command options

    // Constructor
    Parser(int argc, char* argv[]) {
        parseOptions(argc, argv);               // Parse options on initialization
    }

    // Method to parse command line options
void parseOptions(int argc, char* argv[]) {
    int opt;
    // Use getopt to parse options with arguments
    while ((opt = getopt(argc, argv, "e:i:o:b:")) != -1) {
        switch (opt) {
            case 'e': {
                std::istringstream iss(optarg);
                std::string arg;
                getline(iss, options.execName, ' ');  // Extract the executable name
                while (getline(iss, arg, ' ')) {     // Extract arguments for the executable
                    options.execArgs.push_back(arg);
                }
                break;
            }
            case 'i':
                options.inputFile = optarg;         // Set input file
                break;
            case 'o':
                options.outputFile = optarg;        // Set output file
                break;
            case 'b':
                options.inputFile = optarg;         // Set both input and output to the same file
                options.outputFile = optarg;
                break;
            default:
                std::cerr << "Usage: mync -e \"<exec> <args>\" -i <inputFile> -o <outputFile> -b <bothFile>" << std::endl;
                exit(EXIT_FAILURE);
        }
    }

    // Ensure there are remaining arguments for protocol and port
    if (optind < argc) {
        options.protocol = argv[optind++];
        if (optind < argc) {
            options.port = std::stoi(argv[optind]);
        }
    } else {
        std::cerr << "Expected protocol and port after options." << std::endl;
        exit(EXIT_FAILURE);
    }
}


    // Getter for port
    int getPort() const {
        return options.port;
    }

    // Getter for executable name
    std::string getExecName() const {
        return options.execName;
    }

    // Getter for executable arguments
    std::vector<std::string> getExecArgs() const {
        return options.execArgs;
    }
};
