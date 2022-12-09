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

int main(int argc, char* argv[]){
    //char welcome_msg[] = "Hello from server!\n";
    unsigned long ip_clients[1000] = {};
    int number_of_clients = 0;
    char msg_from_client[1000];

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
        sockaddr_in cs_addr;
        socklen_t cs_addrsize = sizeof (cs_addr);
        int client_socket = accept(server_socket, (struct sockaddr *) &cs_addr, &cs_addrsize);

        printf("New client! IP = %s\n", inet_ntoa(cs_addr.sin_addr));
        ip_clients[number_of_clients] = cs_addr.sin_addr.s_addr;
        number_of_clients += 1;

        printf("Number of clients = %d\n", number_of_clients);
        for (int i = 0; i < number_of_clients; i++) {
            // Socket
            int client_socket_local = socket(AF_INET, SOCK_STREAM, 0);
            
            // Client address
            struct sockaddr_in client_address_local = {0};
            client_address_local.sin_family = AF_INET;
            client_address_local.sin_port = htons(60000);
            //struct in_addr client_addres = {};
            //client_addres.s_addr = ip_clients[i];
            //client_address_local.sin_addr = client_addres;

            if (connect(client_socket_local, (struct sockaddr *) &client_address_local, sizeof(client_address_local)) < 0) {
		        printf("Error! Can't connet to remote socket\n\n");
	        }

            send(client_socket, (const void*) ip_clients, sizeof(unsigned long) * 1000, 0);

            close(client_socket_local);
        }

        close(client_socket);
    }

    close(server_socket);

	return 0;
}