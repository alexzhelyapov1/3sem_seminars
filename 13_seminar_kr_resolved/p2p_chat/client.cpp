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

struct client_info{
    in_addr addr;
    in_port_t port;
};

void print_users_list(client_info* clients_list, int number_of_clients) {
    printf("\nStart of list*\n");
    for (int i = 0; i < number_of_clients; i++) {
        printf("Client #%d, IP = %s, port = %hu\n", i, inet_ntoa(clients_list[i].addr), clients_list[i].port);
    }
    printf("End of list*\n\n");
}

// int accept_new_socket()


int main() {
	client_info users_list[1000] = {0};
	int size_of_users_list = 1000 * sizeof(client_info);

    // Socket
	int server_socket = socket(AF_INET, SOCK_STREAM, 0);

	// Server address
	struct sockaddr_in server_address = {0};
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);

	int server_connection = connect(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));
	if (server_connection < 0) {
		printf("Error! Can't establish connection to remote socket\n\n");
		return -1;
	}

	char welcome_msg[1000] = "Hi! I'am client.\n";
	printf("Sending msg...\n");
	send(server_socket, welcome_msg, sizeof(welcome_msg), 0);

	char server_response[1000];
	printf("Waiting for reply...\n");
	recv(server_socket, &server_response, sizeof(server_response), 0);
	printf("Received msg:\n%s", server_response);


	// PROBLEM! Not always receive correct id. Sometimes it returns 0.
	int my_id = 0;
	int received = recv(server_socket, (void*) &my_id, sizeof(my_id), 0);
	printf("Received = %d bytes\n", received);
	printf("My id = %d\n\n", my_id);

	//recv(server_socket, (void*) users_list, size_of_users_list, 0);
	// printf("Received list!!!\n");
	print_users_list(users_list, 5);

	close(server_socket);

	return 0;
}