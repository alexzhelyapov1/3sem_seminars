// This programm send linux commands to another one
#include "msg.h"

int main() {

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


    struct msg_struct m = {};
        

    m.type = 1;
    char s[1000];
    
    // Enter commands in cicle and send it:
    // -------------------------------------------------------------------------------------------------------------  

    while (1) {
        int i = 0;
        s[i] = '\0';

        while (1) {
            scanf("%c", s + i);

            if (s[i] == '\n') break; 
            i++;
        }
        s[i] = '\0';

        printf("You entered the command = %s\n", s);
        strcpy(m.data, s);

        if (strlen(s) <= 0 || msgsnd(descryptor, &m, sizeof(struct msg_struct) - sizeof(long), 0) < 0) 
            printf("Not sended\n");

        else  
            printf("Sended\n");

        s[0] = '\0';
    }

    // -------------------------------------------------------------------------------------------------------------

    return 0;
}