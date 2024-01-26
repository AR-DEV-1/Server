// server.hpp

#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX_CLIENTS 5
#define BUFFER_SIZE 1024

class Server {
public:
    Server();
    ~Server();

    void init(int port);
    void startListening();
    int acceptConnection();
    void handleClient(int clientSocket);
    void closeServer();

private:
    int serverSocket;
    sockaddr_in serverAddress;
};

#endif  // SERVER_HPP
