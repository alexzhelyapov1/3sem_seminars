// Theory
// ---------------------------------------------------------------------------------------------------------------------
// ftok()
// msgget()
// msgsnd()
// msgrcv():
//          msgtype = 0  - принимает верхнее сообщение
//                  = 4  - принимает конкретно 4
//                  = -5 - принимает от 1 до 5
// ---------------------------------------------------------------------------------------------------------------------

#include "msg.h"

int main() {
    int key = 0;
    if (!(key = ftok(path, 0))) printf("Error in ftok, key = %d\n", key);

    int descryptor = msgget(key, 0666 | IPC_CREAT);
    if (descryptor < 0) printf("Error descryptor = %d", descryptor);

    struct msg_struct m1 = {};
    m1.type = 1;
    strcpy(m1.data, "Hello world\n");
    if (msgsnd(descryptor, &m1, sizeof(struct msg_struct) - sizeof(long), 0) < 0)
        printf("Not sended\n");
    else 
        printf("Sended\n");

    return 0;
}

