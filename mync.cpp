#include <cstdlib>
#include <string>
#include <vector>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

#include "Parser.hpp"
#include "TCPhandler.hpp"

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
        execvp(args[0], const_cast<char *const *>(args));
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

int main(int argc, char *argv[])
{
    Parser parser(argc, argv); // Initialize parser with command-line arguments
    if (!parser.tArgs.empty())
    {                                     // if the timeout argument is not null then set the timeout
        int timeout = stoi(parser.tArgs); // convert the timeout argument to an integer
        alarm(timeout);                   // set the timeout
    }

    cout << "DEBUG PRINT: DELETE LATER! before updating the inputfd and the outputfd in the main: " << "input_fd: " << input_fd << " output_fd: " << output_fd << endl;

    if (!parser.iArgs.empty()) parser.makeServerByFlag(input_fd, parser.extractNumbers(parser.iArgs)); // make the server (input) by flag
    if (!parser.oArgs.empty()) parser.makeClientByFlag(output_fd, parser.extractNumbers(parser.oArgs)); // make the client by flag
    if (!parser.bArgs.empty()){
        parser.makeServerByFlag(input_fd, parser.extractNumbers(parser.bArgs));
    }

    cout << "DEBUG PRINT: DELETE LATER! State after - input_fd: " << input_fd << ", output_fd: " << output_fd << endl;

    if (parser.execArgs != NULL)
    {
        std::cout << "DEBUG PRINT: DELETE LATER! inside the eArgs if scope" << std::endl;
        pid_t pid = fork();
        if (pid < 0)
        {
            perror("fork failed");
            cleanup();
        }
        else if (pid > 0){
            int status;
            waitpid(pid, &status, 0);
            close(input_fd);
            close(output_fd);
            return 0;
        }
        else
        {
            std::cout << "DEBUG PRINT: DELETE LATER! fork = 0 at this point" << std::endl;
            // ifs to applay dups
            if (!parser.iArgs.empty())
            {
                dup2(input_fd, STDIN_FILENO); // Redirect input to the input_fd socket file descriptor = 0
            }
            else if (!parser.oArgs.empty())
            {
                dup2(output_fd, STDOUT_FILENO); // Redirect output to the output_fd socket file descriptor = 1
            }
            else if (!parser.bArgs.empty())
            {
                dup2(output_fd, STDOUT_FILENO); // Redirect output to the output_fd socket file descriptor = 1
                dup2(input_fd, STDIN_FILENO);   // Redirect input to the input_fd socket file descriptor = 0
            }
            executeCommand(parser.execArgs); // execute the execvp command
            perror("execvp failed");
            cleanup();
        }
    }else{ // make a chat between the server and the client
            cout << "DEBUG PRINT: DELETE LATER! this is the point inside the eArgs else scope" << endl;

            if (!parser.iArgs.empty())
            {
                tcpConv(input_fd);
                std::cout << "inside the server talker if" << std::endl;
            }
            else if (!parser.oArgs.empty())
            {
                tcpConv(output_fd);
            }
        }

        cout << "DEBUG PRINT: DELETE LATER! just befor the \"RETURN\"" << endl;
        cleanup();
        return 0;
    }
