// main.c

#include "include/server.h"

int main() {
    const int PORT = 8080;
    Server server;
    int client_socket;

    init_server(&server, PORT);
    start_listening(&server);

    while (1) {
        printf("Waiting for connections...\n");
        client_socket = accept_connection(&server);
        printf("Connection accepted\n");

        handle_client(client_socket);
    }

    close_server(&server);

    return 0;
}
