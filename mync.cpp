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

    cout << "DEBUG PRINT: DELETE LATER! this is the point before updating the input and the output in the main" << endl;
    cout << "DEBUG PRINT: DELETE LATER! this is the state of input_fd before: " << input_fd << endl;
    cout << "DEBUG PRINT: DELETE LATER! this is the state of output_fd before: " << output_fd << endl;


    if (!parser.iArgs.empty()) parser.makeServerByFlag(input_fd, parser.extractNumbers(parser.iArgs));
    if (!parser.oArgs.empty()) parser.makeClientByFlag(output_fd, parser.extractNumbers(parser.oArgs));

        if (!parser.bArgs.empty()){

          //  parser.updateInputOutput(input_fd, output_fd, 0);
        }
    cout << "DEBUG PRINT: DELETE LATER! this is the state of input_fd after: " << input_fd << endl;
    cout << "DEBUG PRINT: DELETE LATER! this is the state of output_fd after: " << output_fd << endl;
    cout << "DEBUG PRINT: DELETE LATER! this is the point before chaking if eArg is null" << endl;
    cout << parser.eArgs[0] << endl;
    cout << parser.eArgs[1] << endl;
    if (parser.eArgs[0] != "" && parser.eArgs[1] != ""){
        cout << "DEBUG PRINT: DELETE LATER! this is the just inside the earg check" << endl;
        // redirect the input and output to the new file descriptors
        // if (input_fd != STDIN_FILENO)
        // {
        //     if (dup2(input_fd, STDIN_FILENO) == -1)
        //     {
        //         perror("input dup2 failed");
        //         cleanup();
        //     }
        // }

        if (output_fd != STDOUT_FILENO)
        {
            std::cout << "this is the out dup print" << std::endl;
            if (dup2(output_fd, STDOUT_FILENO) == -1)
            {
                perror("output dup2 failed");
                cleanup();
            }
        }
        cout << "DEBUG PRINT: DELETE LATER! this is the point befor the executeCommand" << endl;
        executeCommand(parser.execArgs);
    }else{              //make a chat between the server and the client
        cout << "DEBUG PRINT: DELETE LATER! this is the point inside the eArgs else scope" << endl;
        
        if(!parser.iArgs.empty()){
            tcpConv(input_fd);
            std::cout << "inside the server talker if" << std::endl;
        }
        else if(!parser.oArgs.empty()){
            tcpConv(output_fd);
        }          
    }
    cout << "DEBUG PRINT: DELETE LATER! this is the point after the if eArgs not null scope" << endl;
    cleanup();
    return 0;
}
