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

    struct msg_struct m;

    bool end = false;
    if (msgrcv(descryptor, &m, sizeof(struct msg_struct) - sizeof(long), 0, 0) >= 0) {
        printf("Msg received:\n");
        printf("%s", m.data);
    }
    else
        printf("Cant receive msg\n");

    if (msgctl(descryptor, IPC_RMID, NULL) == 0) {
        printf("Memory deleted successfully\n");
    }
    return 0;
}

