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
#include <arpa/inet.h>
#include <string.h>

struct client_info{
    in_addr addr;
    in_port_t port;
};

void print_clients_list(client_info* clients_list, int number_of_clients) {
    printf("\nStart of list*\n");
    for (int i = 0; i < number_of_clients; i++) {
        printf("Client #%d, IP = %s, port = %hu\n", i, inet_ntoa(clients_list[i].addr), clients_list[i].port);
    }
    printf("End of list*\n\n");
}

int sendall(int s, char* buf, int len, int flags) {
    int total = 0;
    int n;

    while (total < len) {
        n = send(s, buf + total, len - total, flags);
        if (n == -1) {break;}
        total += n;
    }

    return (n == -1 ? -1 : total);
}

void mailing_new_clients_list(client_info* clients_list, int number_of_clients) {
    int size_of_msg = 1100;
    // New socket for old clients
    for (int i = 0; i < number_of_clients; i++) {
        int old_client_socket = socket(AF_INET, SOCK_STREAM, 0);
        // Client address
        struct sockaddr_in old_client_addr = {0};
        old_client_addr.sin_family = AF_INET;
        old_client_addr.sin_addr = clients_list[i].addr;
        old_client_addr.sin_port = htons(60000 + i);

        int connection_old_client = connect(old_client_socket, (struct sockaddr *) &old_client_addr, sizeof(old_client_addr));
        if (connection_old_client < 0) {
            printf("Error! Can't connet to\n");
            printf("Client #%d, IP = %s, port = %hu\n\n", i, inet_ntoa(clients_list[i].addr), clients_list[i].port);
            continue;
        }
        printf("Sended to client #%d, IP = %s, port = %hu\n\n", i, inet_ntoa(clients_list[i].addr), clients_list[i].port);
        char msg[1100];
        memcpy(msg + 100, clients_list, 1000);
        msg[0] = 1;
        sendall(old_client_socket, (char*) msg, size_of_msg, 0);
        close(old_client_socket);
    }
}

int main(int argc, char* argv[]){
    char welcome_msg_to_client[] = "Hello from server!\n";
    char msg_from_client[1000] = {};
    client_info clients_list[1000];
    
    int number_of_clients = 0;

    // Socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // Server adress
    int server_port = 9002;
    struct sockaddr_in server_address = {0};
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(server_port);
    printf("Server is up. Port is %d\n", server_port);

    // Bind socket to server adress
    bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));

    // Listen for requests
    listen(server_socket, 100);

    while (1) {
        printf("--------------------\n");
        sockaddr_in new_client_addr;
        socklen_t new_client_addrsize = sizeof (new_client_addr);
        int client_socket = accept(server_socket, (struct sockaddr *) &new_client_addr, &new_client_addrsize);

        printf("New client! IP = %s, port = %hu\n", inet_ntoa(new_client_addr.sin_addr), new_client_addr.sin_port);

        printf("Number of clients = %d\n", number_of_clients);

        recv(client_socket, &msg_from_client, sizeof(msg_from_client), 0);
        printf("Received msg from clien:\n%s\n", msg_from_client);

        sendall(client_socket, welcome_msg_to_client, sizeof(welcome_msg_to_client), 0);  // Send welcome
        int sended = sendall(client_socket, (char*) &number_of_clients, sizeof(number_of_clients), 0);  // Send id
        printf("Sended = %d bytes\n", sended);

        clients_list[number_of_clients].addr = new_client_addr.sin_addr;
        clients_list[number_of_clients].port = new_client_addr.sin_port;
        number_of_clients += 1;

        mailing_new_clients_list(clients_list, number_of_clients);
        print_clients_list(clients_list, number_of_clients);
        close(client_socket);
        printf("--------------------\n");
    }

    close(server_socket);

    free(clients_list);
	return 0;
}