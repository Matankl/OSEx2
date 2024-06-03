#include "parser.hpp"
#include <cstdlib>
#include <string>

int main(int argc, char* argv[]) {
    Parser parser(argc, argv);  // Initialize parser with command-line arguments

    // Example usage of parsed data
    std::cout << "Executable: " << parser.getExecName() << std::endl;
    for (const auto& arg : parser.getExecArgs()) {
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





// #include <unistd.h> // For execvp
// #include <cstdlib> // For exit
// #include <cstring> // For strcmp

// #define DESTADDR "127.0.0.1"



// // this class mimics netcut
// // for -i input file
// // for -o output file
// // for -b input and output file
// // for -e the name of the executable file and its arguments

    
// int main(int argc, char const *argv[]){
//     // get the correct port

//     while (string option_val = getopt(argc, argc, "e:i:o:b")){
//         switch (option_val)
//         {
//         case e:
//             string exec_name = optarg;

//         case i:
            
//             break;
            
//         case o:
                 
//             break;

//         case b:

//             break;
        
//         default:

//             break;
//         }        
//     }

    


    
    
// //     //open socket with the correct port
// //     int createUdpTalker(){ 
// // 	int sockfd;
// // 	struct addrinfo hints, *servinfo, *p;
// // 	int rv;
// // 	int numbytes;
// // 	memset(&hints, 0, sizeof hints);
// // 	hints.ai_family = AF_INET; // set to AF_INET to use IPv4
// // 	hints.ai_socktype = SOCK_DGRAM;

// // 	if ((rv = getaddrinfo(DESTADDR, SERVERPORT, &hints, &servinfo)) != 0) {
// // 		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
// // 		return 1;
// // 	}

// // 	for(p = servinfo; p != NULL; p = p->ai_next) {
// // 		if ((sockfd = socket(p->ai_family, p->ai_socktype,
// // 				p->ai_protocol)) == -1) {
// // 			perror("talker: socket");
// // 			continue;
// // 		}

// // 		break;
// // 	}
// // 	connect (sockfd, p->ai_addr, p->ai_addrlen);
// // 	return sockfd;
// // }




     




    

//     return 0;
// }




