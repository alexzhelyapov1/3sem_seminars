#include "msg.h"

int main() {
    long int ttime = time(NULL);
    printf ("Process 1 started at %s\n", ctime(&ttime));

//  Open msgs
// ---------------------------------------------------------------------------------------------------------------------

    int key = 0;
    if (!(key = ftok(path, 0))) printf("Error in ftok, key = %d\n", key);

    int descryptor = msgget(key, 0666 | IPC_CREAT);
    if (descryptor < 0) printf("Error descryptor = %d", descryptor);

// ---------------------------------------------------------------------------------------------------------------------

    ttime = time(NULL);
    printf("I am waiting second programm... Time = %s\n", ctime(&ttime));


// Waiting reply
// ---------------------------------------------------------------------------------------------------------------------

    struct msg_struct m;
    if (msgrcv(descryptor, &m, sizeof(struct msg_struct) - sizeof(long), 1, 0) >= 0) {
        printf("Msg received\n");
    }
    else
        printf("Cant receive msg\n");

// ---------------------------------------------------------------------------------------------------------------------

    ttime = time(NULL);
    printf("I waited! Proccess 2 ended. Time = %s\n", ctime(&ttime));

    if (msgctl(descryptor, IPC_RMID, NULL) == 0) {
        printf("Memory deleted successfully\n");
    }
    return 0;
}