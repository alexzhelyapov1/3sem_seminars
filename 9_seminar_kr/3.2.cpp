// This programm receive linux commands and executes them

#include "msg.h"
#include <unistd.h>


int main(int argc, char **argv) {

    // Open msgs
    // -------------------------------------------------------------------------------------------------------------

    int key = 0;
    if (!(key = ftok(path, 0))) printf("Error in ftok, key = %d\n", key);

    int descryptor = msgget(key, 0666 | IPC_CREAT);
    if (descryptor < 0) printf("Error descryptor = %d", descryptor);

    // -------------------------------------------------------------------------------------------------------------

    struct msg_struct m = {};

    int id = 0;

    while (1) {
        if (msgrcv(descryptor, &m, sizeof(struct msg_struct) - sizeof(long), 1, 0) >= 0) {
            printf("Received: %s\n", m.data);
            char* a[2];
            a[0] = m.data;
            a[1] = NULL;

            id = fork();
            if (id == 0) {
                // printf("I am new proc\n");
                char cmd[100];
                char* args[100];

                sscanf(m.data, "%s", cmd);
                // printf("Cmd = %s\n", cmd);

                args[0] = cmd;
                int j = 1;
                int i = strlen(cmd);
                int global_len = strlen(m.data);
                while (i < global_len) {
                    // printf("Char = \"%c\" ", m.data[i]);
                    if (m.data[i] == ' ' || m.data[i] == '\n') {
                        m.data[i] = '\0';
                        args[j] = m.data + i + 1;
                        // printf("New char = %d\n", 0);
                        j++;
                    }
                    i++;
                }

                args[j] = NULL;

                // printf("Args = %d\n", j);
                // for (int i = 0; args[i] != NULL; i++) {
                //     printf("Parsed args = %s\n", args[i]);
                // }

                
                execvp(cmd, args);
                return 0;
            }
        }
    }

    return 0;
}