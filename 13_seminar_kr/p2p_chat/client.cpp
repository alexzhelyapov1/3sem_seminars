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

int main() {
    // Socket
	int network_socket = socket(AF_INET, SOCK_STREAM, 0);
	
    // Server address
	struct sockaddr_in server_address = {0};
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);

	if (connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address)) < 0) {
		printf("Error! Can't connet to remote socket\n\n");
	}
	
	unsigned long server_response[1000];
	char msg[1000] = "Hi! I'am client.\n";

	int my_socket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in my_address = {0};
    my_address.sin_family = AF_INET;
    my_address.sin_port = htons(60000);
    bind(my_socket, (struct sockaddr*) &my_address, sizeof(my_address));

	//send(network_socket, msg, sizeof(msg), 0);
	printf("Sent to server: %s\n", msg);
	recv(my_socket, &server_response, sizeof(unsigned long) * 1000, 0);
	printf("Received ip list!\n");

	close(network_socket);

	return 0;
}