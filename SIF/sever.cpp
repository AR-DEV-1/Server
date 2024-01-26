// server.cpp

#include "server.hpp"

Server::Server() {
    serverSocket = -1;
    std::memset(&serverAddress, 0, sizeof(serverAddress));
}

Server::~Server() {
    closeServer();
}

void Server::init(int port) {
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);

    if (bind(serverSocket, reinterpret_cast<struct sockaddr *>(&serverAddress), sizeof(serverAddress)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }
}

void Server::startListening() {
    if (listen(serverSocket, MAX_CLIENTS) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }
}

int Server::acceptConnection() {
    int clientSocket;
    if ((clientSocket = accept(serverSocket, nullptr, nullptr)) < 0) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }
    return clientSocket;
}

void Server::handleClient(int clientSocket) {
    char buffer[BUFFER_SIZE];
    int readSize;

    while ((readSize = read(clientSocket, buffer, sizeof(buffer))) > 0) {
        write(clientSocket, buffer, readSize);  // Echo back to the client
    }

    if (readSize == 0) {
        std::cout << "Client disconnected" << std::endl;
    } else if (readSize == -1) {
        perror("Recv failed");
    }

    close(clientSocket);
}

void Server::closeServer() {
    if (serverSocket != -1) {
        close(serverSocket);
    }
}
