#include <iostream>
#include <unistd.h> // For execvp
#include <cstdlib> // For exit
#include <cstring> // For strcmp

int main(int argc, char *argv[]) {
    // Check if the program name and at least one argument are provided
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " -e <program> [arguments...]" << std::endl;
        return 1;
    }

    // Check if the -e option is provided
    if (strcmp(argv[1], "-e") != 0) {
        std::cerr << "Option -e is missing" << std::endl;
        return 1;
    }

    // Ensure that at least one argument is provided after the -e option
    if (argc < 3) {
        std::cerr << "Program name is missing" << std::endl;
        return 1;
    }

    // Ensure that it got a pramiter after the program name
    if (argc < 4) {
        std::cerr << "Program parameter is missing" << std::endl;
        return 1;
    }

    // Execute the program with the provided arguments
    if (execvp(argv[2], argv + 2) == -1) {
        // If execvp returns -1, it means an error occurred
        perror("execvp");
        return 1;
    }

    // execvp replaces the current process, so this code is reached only if an error occurs
    return 1;
}
