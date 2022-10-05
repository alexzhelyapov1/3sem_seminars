#include "chat.h"



int main() {
    // int user_id = 0;
    // printf("Please enter your user_id:\n");
    // scanf("%d", &user_id);
    char msg[1000];
    int result = 0;
    char command;
    char* mem;
    int descriptor = 0;

    const char* path_mine1 = "~/Desktop/root/infa/3sem_seminars/5_seminar/chat_with_commands/chat.cpp";
    OpenSharedMemory(path_mine1, &mem, &descriptor);

    printf("Commands: \nr - receive message \ns - send message (s \"Your text\")\nq - quit chat\n");
    while(1) {
        scanf("%c", &command);
        if (command == 'r') {
            strcpy(msg, mem);
            printf("Received message:\n");
            printf("%s\n", msg);
        }
        else if (command == 's') {
            int i = 0;
            scanf("%c", &command);
            while ((result = scanf("%c", msg + i)) > 0 && msg[i] != '\n') i++;
            msg[i] = '\0';
            strcpy(mem, msg);
            printf("Sending message...\n");
        }
        else if (command == 'q') {
            break;
        }
        else {
            // printf("Can't recognize command\n");
        }
    }
    shmdt(mem);
    shmctl(descriptor, IPC_RMID, NULL);
    printf("Good bye");
    return 0;
}