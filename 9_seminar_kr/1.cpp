// This programm create 5 fork processes and send them msgs. When they receive them, the print hello.

#include "msg.h"
#include "sys/types.h"
#include "unistd.h"

int main() {
    int n = 5;
    int id = 0;

    // Clean old messages
    // -------------------------------------------------------------------------------------------------------------

    int key = 0;
    if (!(key = ftok(path, 0))) printf("Error in ftok, key = %d\n", key);

    int descryptor = msgget(key, 0666 | IPC_CREAT);
    if (descryptor < 0) printf("Error descryptor = %d", descryptor);

    if (msgctl(descryptor, IPC_RMID, NULL) == 0) {
        printf("Memory deleted successfully\n");
    }

    // -------------------------------------------------------------------------------------------------------------


    // Reopen msgs
    // -------------------------------------------------------------------------------------------------------------

    descryptor = msgget(key, 0666 | IPC_CREAT);
    if (descryptor < 0) printf("Error descryptor = %d", descryptor);

    // -------------------------------------------------------------------------------------------------------------


    int* list = (int*) calloc(sizeof(int), n);

    // Create n new processes
    // -----------------------------------------------------------------------------------------------------------------

    for (int i = 0; i < n; i++) {
        // printf("I am process number %d\n", getpid());
        // printf("Creating new process\n");

        // If I am child
        if ((id = fork()) == 0) break;

        list[i] = id;
    }

    // -----------------------------------------------------------------------------------------------------------------


    // Check list of proc
    // -----------------------------------------------------------------------------------------------------------------

    if (id != 0) {
        printf("List: ");
        for (int i = 0; i < n; i++) {
            printf("%d ", list[i]);
        }
        printf("\n");
    }

    // -----------------------------------------------------------------------------------------------------------------


    // Sending them msg if I am parent
    // -----------------------------------------------------------------------------------------------------------------

    if (id != 0) {

        struct msg_struct m = {};
        
        for (int i = 0; i < n; i++) {
            m.type = list[i];

            if (msgsnd(descryptor, &m, sizeof(struct msg_struct) - sizeof(long), 0) < 0) ;
                // printf("Not sended\n");

            else  ;
                // printf("Sended to %d\n", list[i]);
        }

        // printf("All msgs are sended!\n");
    }

    // -----------------------------------------------------------------------------------------------------------------


    // Receiving msg if I am child
    // -----------------------------------------------------------------------------------------------------------------

    if (id == 0) {

        struct msg_struct m = {};

        if (msgrcv(descryptor, &m, sizeof(struct msg_struct) - sizeof(long), getpid(), 0) >= 0) {
            printf("I am proc number %d, received msg!\n", getpid());
        }
    }

    // -----------------------------------------------------------------------------------------------------------------

    free(list);
    return 0;
}