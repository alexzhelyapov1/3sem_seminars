#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>     
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <pthread.h>

struct client_info{
    in_addr addr;
    in_port_t port;
};


client_info users_list[1000] = {0};
int number_of_users = 0;
int my_id = -1;



void print_users_list(client_info* clients_list, int number_of_clients) {
    printf("\nStart of list*\n");
    for (int i = 0; i < number_of_clients; i++) {
        printf("Client #%d, IP = %s, port = %hu\n", i, inet_ntoa(clients_list[i].addr), clients_list[i].port);
    }
    printf("End of list*\n\n");
}

void msg_send(int id_target, char* buffer) {
	struct sockaddr_in target_addr = {0};
	target_addr.sin_addr = users_list[id_target].addr;
	target_addr.sin_port = users_list[id_target].port;

	int target_socket = socket(AF_INET, SOCK_STREAM, 0);

	int target_connection = connect(target_socket, (struct sockaddr*) &target_addr, sizeof(target_addr));
	if (target_connection < 0) {
		printf("Error! Can't connect to client [%d]\n", id_target);
	}

	send(target_socket, buffer, strlen(buffer), 0);

	close(target_socket);
}

void *msg_send_loop(void *arg) {
	printf("-----MSG started\n");
	char buffer[1000];
	int i = 0;
	int id_target = 0;

	while (id_target != -1) {
		scanf("%d", &id_target);
		while (i < 999 && ((buffer[i] = getchar()) != '\n')) i++;
		buffer[i] = '\0';

		msg_send(id_target, buffer);
		printf("Sended to [%d], msg: \n", id_target);
	}
}

void *check_update_loop(void *arg) {
	printf("-----UPDATE started\n");
	int update_socket = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in update_addr = {0};
	update_addr.sin_family = AF_INET;
	update_addr.sin_port = htons(60000 + my_id);
	
	bind(update_socket, (struct sockaddr*) &update_addr, sizeof(update_addr));

	listen(update_socket, 100);

	while (1) {
        int companion_socket = accept(update_socket, 0, 0);

		char msg_from_client[4000];
        recv(companion_socket, &msg_from_client, sizeof(msg_from_client), 0);
        printf("Received msg from someone:\n%s\n", msg_from_client);

		if (msg_from_client[0] == 1) {		//Update users list
			memcpy(users_list, msg_from_client + 100, 1000);
			number_of_users += 1;
			print_users_list(users_list, number_of_users + 1);
		}

		else if (msg_from_client[0] == 2) {	//New msg
			int sender_id = *((int*) (msg_from_client + 1));
			printf("[%d] %s\n", sender_id, (msg_from_client + 100));
		}

		close(companion_socket);
    }

	close(update_socket);
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


int main() {
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
	recv(server_socket, &server_response, 20, 0);
	printf("Received msg:\n%s", server_response);


	// PROBLEM! Not always receive correct id. Sometimes it returns 0.
	int received = recv(server_socket, (void*) &my_id, sizeof(my_id), 0);
	printf("Received = %d bytes\n", received);
	printf("My id = %d\n\n", my_id);

	//if (my_id == -1) {printf("Error! Didn't receive my id!\n"); return -1;}

	
	pthread_t thread_1 = {0};
	pthread_t thread_2 = {0};
    if (pthread_create(&thread_1, NULL, check_update_loop, NULL)) {
        printf("Error! Thread 1 did not create\n");
    }
	if (pthread_create(&thread_2, NULL, msg_send_loop, NULL)) {
		printf("Error! Thread 1 did not create\n");
	}
	pthread_join(thread_1, NULL);
	pthread_join(thread_2, NULL);
	

	//recv(server_socket, (void*) users_list, size_of_users_list, 0);
	// printf("Received list!!!\n");
	print_users_list(users_list, number_of_users);

	close(server_socket);

	return 0;
}