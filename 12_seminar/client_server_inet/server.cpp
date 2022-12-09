#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>     
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char* argv[]){
    char welcome_msg[] = "Hello from server!\n";
    char msg_to_client[1000];

    // Socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // Server adress
    struct sockaddr_in server_address = {0};
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);

    // Bind socket to server adress
    bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));

    // Listen for requests
    listen(server_socket, 100);

    while (1) {
        int client_socket = accept(server_socket, NULL, NULL);
        recv(client_socket, &msg_to_client, sizeof(msg_to_client), 0);
        printf("Client sent to me:\n%s\n", msg_to_client);
        send(client_socket, welcome_msg, sizeof(welcome_msg), 0);
    }

    close(server_socket);

	return 0;
}