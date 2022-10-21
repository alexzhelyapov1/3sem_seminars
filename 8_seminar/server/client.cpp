#include "msg.h"

// type = 1 - new client
//      = 2 - get my id
//      = 3 - new user added, update list

int get_descryptor() {
    int key = 0;
    if (!(key = ftok(path, 0))) printf("Error in ftok, key = %d\n", key);

    int descryptor = msgget(key, 0666 | IPC_CREAT);
    if (descryptor < 0) printf("Error descryptor = %d", descryptor);
    return descryptor;
}

// Return id of client.
int new_client(int descryptor) {
    struct msg_struct m = {};
    m.type = 1;
    strcpy(m.data, "Hello world\n");
    if (msgsnd(descryptor, &m, sizeof(struct msg_struct) - sizeof(long), 0) < 0)
        printf("Not sended\n");

    else 
        printf("Sended\n");


    // Waiting my id
    if (msgrcv(descryptor, &m, sizeof(struct msg_struct) - sizeof(long), 2, 0) >= 0) {
        printf("Msg received:\n");
        printf("My id is %d\n", m.to);
        return m.to;
    }

    else
        printf("Cant receive msg\n");
        return -1;
}





int main() {
    int descryptor = get_descryptor();
    int my_id = new_client(descryptor);
    int clients_list[100] = {};
    clients_list[0] = -1;

    
}