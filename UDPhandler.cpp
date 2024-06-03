
int udpServer(port){
    //init socket
    int serverSocket = socket(AF_INET, SOCK_DGRAM, 0);
    
    //fill in the server address
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
    return serverSocket;
}

int udpClient(int port){
    //init socket
    int clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
    
    //fill in the server address
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    
    return clientSocket;
}