#include "msg.h"

// type = 1 - new client
//      = 2 - get my id
//      = 3 - new user added, update list

int get_descryptor() {
    int key = 0;
    if (!(key = ftok(path, 0))) printf("Error in ftok, key = %d\n", key);

    int descryptor = msgget(key, 0666 | IPC_CREAT);
    if (descryptor < 0) printf("Error descryptor = %d\n", descryptor);
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

void print_list (int* list) {
    for (int i = 0; list[i] != -1; i++)
        printf("%d ", list[i]);
    printf("\n");
}

void receive_msg(int descryptor, int my_id, int* clients_list) {
    struct msg_struct m;

    if (msgrcv(descryptor, &m, sizeof(struct msg_struct) - sizeof(long), my_id, 0) >= 0) {
        printf("Msg received:\n");
        printf("%s", m.data);

        if (strcmp(m.data, "New clients") == 0) {
            int* new_list = (int*) (m.data + size_of_info);
            int i = 0;
            for (i = 0; new_list[i] != -1; i++) {
                clients_list[i] = new_list[i];
            }
            clients_list[i] = -1;
            printf ("New clients list received!!!\n");
            print_list(clients_list);
        }
    }

    else
        printf("Cant receive msg\n");
}



int main() {
    int descryptor = get_descryptor();
    int my_id = new_client(descryptor);
    int clients_list[100] = {};
    clients_list[0] = -1;
    // receive_msg(descryptor, my_id, clients_list);

    char s[100];
    while (true) {
        if (scanf("%s", s) > 0) {
            if (strcpy(s, "r"))
                receive_msg(descryptor, my_id, clients_list);

            else if (strcpy(s, "s")) {
                // send_msg(descryptor, my_id);
            }
            
            else if (strcpy(s, "l")) {
                print_list(clients_list);
            }
        }
    }
}