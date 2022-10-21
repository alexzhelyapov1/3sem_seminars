#include "msg.h"

int get_descryptor() {
    // Deleting msg queue
    int key = 0;
    if ((key = ftok(path, 0)) <= 0) printf("Error in ftok, key = %d\n", key);

    // printf("Key = %d\n", key);
    int descryptor = msgget(key, 0666 | IPC_CREAT);
    if (descryptor < 0) printf("Error descryptor = %d\n", descryptor);
    if (msgctl(descryptor, IPC_RMID, NULL) < -1) printf("Cant delete old queue\n");

    // Making new queue
    if (!(key = ftok(path, 0))) printf("Error in ftok, key = %d\n", key);

    descryptor = msgget(key, 0666 | IPC_CREAT);
    if (descryptor < 0) printf("Error descryptor = %d\n", descryptor);
    printf("Server descryptor = %d\n", descryptor);
    return descryptor;
}

void send_update_clients_list(int descryptor, int* clients_list) { // разослать всем массивы новых клиентов
    int num_of_clients = 0;
    while (clients_list[num_of_clients] != -1) num_of_clients++;

    struct msg_struct m;
    for (int i = 0; i < num_of_clients; i++) {
        m.from = 0;
        m.to = clients_list[i];
        m.type = clients_list[i];

        char info[] = "New clients";
        strcpy(m.data, info);
        memcpy((void*) (m.data + size_of_info), (void*) clients_list, (num_of_clients + 1) * sizeof(int));

        msgsnd(descryptor, &m, sizeof(struct msg_struct) - sizeof(long), 0);
    }
}


int main() {
    int descryptor = get_descryptor();
    int current_new_id = 100;
    int clients_list[100] = {};
    struct msg_struct m;

    while (true) {
        if (msgrcv(descryptor, &m, sizeof(struct msg_struct) - sizeof(long), 1, 0) >= 0) {
            if (!strcmp(m.data, "New user")) {
                m.type = 2;
                m.to = current_new_id;
                clients_list[current_new_id - 100] = current_new_id;
                clients_list[current_new_id - 100 + 1] = -1;
                current_new_id++;

                msgsnd(descryptor, &m, sizeof(struct msg_struct) - sizeof(long), 0);
                send_update_clients_list(descryptor, clients_list);
            }
            else if (!strcmp(m.data, "msg")) {
                m.type = m.to;
                if (msgsnd(descryptor, &m, sizeof(struct msg_struct) - sizeof(long), 0) < 0)
                    printf("Not sended\n");

                else 
                    printf("Sended! Msg: %s\n", m.data + size_of_info);
            }
        }
    }
}