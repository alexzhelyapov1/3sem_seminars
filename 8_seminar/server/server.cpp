#include "msg.h"

int get_descryptor() {
    msgctl(descryptor, IPC_RMID, NULL);

    int key = 0;
    if (!(key = ftok(path, 0))) printf("Error in ftok, key = %d\n", key);

    int descryptor = msgget(key, 0666 | IPC_CREAT);
    if (descryptor < 0) printf("Error descryptor = %d", descryptor);
    return descryptor;
}

send_update_clients_list(int descryptor, int* clients_list) { // разослать всем массивы новых клиентов
    for (int i = 100; i < current_new_id)
    struct msg_struct m;
    m.from = 0;
    m.to = 
    msgsnd(descryptor, &m, sizeof(struct msg_struct) - sizeof(long), 0);
}


int main() {
    int descryptor = get_descryptor;
    int current_new_id = 100;
    int clients_list[100] = {};
    struct msg_struct m;

    while (true) {
        if (msgrcv(descryptor, &m, sizeof(struct msg_struct) - sizeof(long), 1, 0) >= 0) {
            m.type = 2;
            m.to = current_new_id;
            clients_list[current_new_id - 100] = current_new_id;
            clients_list[current_new_id - 100 + 1] = -1;
            current_new_id++;

            msgsnd(descryptor, &m, sizeof(struct msg_struct) - sizeof(long), 0);
            send_update_clients_list(descryptor, current_new_id - 1); //передать массив и доделать
        }
    }
}