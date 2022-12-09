#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>

struct sockaddr_in {
    short int          sin_family;  // Семейство адресов
    unsigned short int sin_port;    // Номер порта
    struct in_addr     sin_addr;    // IP-адрес
    unsigned char      sin_zero[8]; // "Дополнение" до размера структуры sockaddr
};

int main() {
    // Create new socket
    int sockfd = socket(AF_INET, SOCK_STREAM, -0); // Inet TCP

    // Bind socket
    struct sockaddr_in addr = {};
    addr.sin_family

    //if (!bind(sockfd, ))
    
    return 0;
}