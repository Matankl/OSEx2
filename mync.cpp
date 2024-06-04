#include <cstdlib>
#include <string>
#include <vector>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

#include "Parser.hpp"

using namespace std;

int input_fd = STDIN_FILENO;
int output_fd = STDOUT_FILENO;

void cleanup()
{
    if (input_fd != STDIN_FILENO)
        close(input_fd);
    if (output_fd != STDOUT_FILENO)
        close(output_fd);
    exit(EXIT_SUCCESS);
}

void executeCommand(const char **args)
{
    int pid = fork();
    if (pid == 0)
    { // Child process
    cout << "execvp: " << args[0] << endl;
    cout << "execvp: " << args[1] << endl;
        execvp(args[0], const_cast<char* const*>(args));
        perror("execvp failed");
        cleanup(); // Clean up in case of execvp failure
    }
    else if (pid > 0)
    {                   // Parent process
        wait(NULL);     // Wait for the child process to finish
        fflush(stdout); // flash the output
    }
    else
    {
        perror("fork befor execvp failed");
        cleanup(); // Clean up in case of fork failure
    }
}

int main(int argc, char *argv[]){
    Parser parser(argc, argv); // Initialize parser with command-line arguments

    // if the timeout argument is not null then set the timeout
    if (!parser.tArgs.empty())
    {
        // convert the timeout argument to an integer
        int timeout = stoi(parser.tArgs);
        // set the timeout
        alarm(timeout);
    }

    if (!parser.bArgs.empty()) parser.updateInputOutput(input_fd, output_fd, 0);
    if (!parser.iArgs.empty()) parser.updateInputOutput(input_fd, output_fd, 1);
    if (!parser.oArgs.empty()) parser.updateInputOutput(input_fd, output_fd, 2);


    if (parser.eArgs != nullptr)
    {
        // redirect the input and output to the new file descriptors
        if (input_fd != STDIN_FILENO)
        {
            if (dup2(input_fd, STDIN_FILENO) == -1)
            {
                perror("input dup2 failed");
                cleanup();
            }
        }

        if (output_fd != STDOUT_FILENO)
        {
            if (dup2(output_fd, STDOUT_FILENO) == -1)
            {
                perror("output dup2 failed");
                cleanup();
            }
        }
        executeCommand(parser.execArgs);
    }


    // const char* execName = "/bin/ls";  // Example executable
    // const char** execArgs = new const char*[4];  // Example arguments
    // execArgs[0] =  ("123456789");

    // int serverSocket = tcpServer(6000);
    // if (serverSocket < 0) {
    //     cerr << "Failed to create server socket" << endl;
    //     return 1;
    // }

    // int clientSocket = tcpClient(6000);
    // if (clientSocket < 0) {
    //     cerr << "Failed to create client socket" << endl;
    //     return 1;
    // }

    // // Execute command with sockets as stdin and stdout
    // executeCommand(argv[1], const_cast<char* const*>(execArgs), clientSocket, serverSocket);

    return 0;
}
