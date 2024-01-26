// server.h

#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX_CLIENTS 5
#define BUFFER_SIZE 1024

typedef struct {
    int server_socket;
    struct sockaddr_in server_address;
} Server;

void init_server(Server *server, int port);
void start_listening(Server *server);
int accept_connection(Server *server);
void handle_client(int client_socket);
void close_server(Server *server);

#endif  // SERVER_H
