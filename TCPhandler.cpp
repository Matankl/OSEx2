
// this is a method to handle the TCP server
int tcpServer(int port){
//init socket 
int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

//fill in the server address
// sockaddr_in: It is the data type that is used to store the address of the socket.
// htons(): This function is used to convert the unsigned int from machine byte order to network byte order.
// INADDR_ANY: It is used when we don’t want to bind our socket to any particular IP and instead make it listen to all the available IPs.
sockaddr_in serverAddress;
serverAddress.sin_family = AF_INET;
serverAddress.sin_port = htons(port);
serverAddress.sin_addr.s_addr = INADDR_ANY;

//bind the socket to the address
if(bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0){
    // handle binding failure
    cout << "Error binding socket" << endl;
    perror("bind");
    close(serverSocket);
    return -1;
}
// first arg is the socket file descriptor, second arg is the maximum number of connections that can be waiting while the process is handling a particular connection
if(listen(serverSocket, 1) < 0){
    // handle listening failure
    cout << "Error listening on socket" << endl;
    perror("listen");
    close(serverSocket);
    return -1;
}

cout << "Server listening on port " << port << endl;

int clientSocket = accept(serverSocket, nullptr, nullptr);
if(clientSocket < 0){
    // handle accepting failure
    cout << "Error accepting connection" << endl;
    perror("accept");
    close(serverSocket);
    return -1;
}
return clientSocket;
}

// this is a method to handle the TCP client
int tcpClient(int port){
//init socket
int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

//fill in the server address
sockaddr_in serverAddress;
serverAddress.sin_family = AF_INET;
serverAddress.sin_port = htons(port);
serverAddress.sin_addr.s_addr = INADDR_ANY;

//connect to the server
if(connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0){
    // handle connection failure
    cout << "Error connecting to server" << endl;
    perror("connect");
    close(clientSocket);
    return -1;
}

return clientSocket;
}