#include "msg.h"

int main() {
    long int ttime = time(NULL);
    printf ("Proccess 2 started at %s\n", ctime(&ttime));


//  Open msgs
// ---------------------------------------------------------------------------------------------------------------------

    int key = 0;
    if (!(key = ftok(path, 0))) printf("Error in ftok, key = %d\n", key);

    int descryptor = msgget(key, 0666 | IPC_CREAT);
    if (descryptor < 0) printf("Error descryptor = %d", descryptor);

// ---------------------------------------------------------------------------------------------------------------------


// Sending reply msg
// --------------------------------------------------------------------------------------------------------------------- 

    struct msg_struct m1 = {};
    m1.type = 1;
    if (msgsnd(descryptor, &m1, sizeof(struct msg_struct) - sizeof(long), 0) < 0)
        printf("Not sended\n");
    else 
        printf("Sended\n");

// ---------------------------------------------------------------------------------------------------------------------

    printf("I am 2 proc, ended at time = %s\n", ctime(&ttime));
    return 0;
}