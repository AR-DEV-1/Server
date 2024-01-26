// server.c

#include "include/server.h"

void init_server(Server *server, int port) {
    server->server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server->server_socket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server->server_address.sin_family = AF_INET;
    server->server_address.sin_addr.s_addr = INADDR_ANY;
    server->server_address.sin_port = htons(port);

    if (bind(server->server_socket, (struct sockaddr *)&server->server_address, sizeof(server->server_address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }
}

void start_listening(Server *server) {
    if (listen(server->server_socket, MAX_CLIENTS) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }
}

int accept_connection(Server *server) {
    int client_socket;
    if ((client_socket = accept(server->server_socket, NULL, NULL)) < 0) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }
    return client_socket;
}

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    int read_size;

    while ((read_size = read(client_socket, buffer, sizeof(buffer))) > 0) {
        write(client_socket, buffer, read_size);  // Echo back to the client
    }

    if (read_size == 0) {
        puts("Client disconnected");
        fflush(stdout);
    } else if (read_size == -1) {
        perror("Recv failed");
    }

    close(client_socket);
}

void close_server(Server *server) {
    close(server->server_socket);
}
