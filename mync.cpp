#include <cstdlib>
#include <string>

// method to execute the command line arguments
void executeCommand(string execName, vector<string> execArgs, int inputfd, int outputfd)
{
    // execute the command
    if (fork() < 0)
    {
        // handle fork failure
        std::cerr << "Error forking" << std::endl;
        exit(EXIT_FAILURE);
    }

    //fork, change the input and output file descriptors, and execute the command

    

    int main(int argc, char *argv[])
    {
        Parser parser(argc, argv); // Initialize parser with command-line arguments

        // Example usage of parsed data
        std::cout << "Executable: " << parser.getExecName() << std::endl;
        for (const auto &arg : parser.getExecArgs())
        {
            std::cout << "Arg: " << arg << std::endl;
        }
        std::cout << "Protocol: " << parser.options.protocol << std::endl;
        std::cout << "Port: " << parser.getPort() << std::endl;

        // Additional functionality to be implemented as required:
        // - Execute the command

        // - Handle socket communication
        // - Redirect input/output

        return 0;
    }
