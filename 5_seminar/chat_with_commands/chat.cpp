#include "chat.h"

void OpenSharedMemory(const char* path, char** mem_ret, int* descriptor_ret);

int main() {
    char msg[1000];
    int result = 0;
    char command;
    char* mem;
    char* mem_to_send;
    char* mem_to_receive;
    int descriptor = 0;

    const char* path_mine1 = "~/Desktop/root/infa/3sem_seminars/5_seminar/chat_with_commands/chat.cpp";
    OpenSharedMemory(path_mine1, &mem, &descriptor);
    printf ("Returned descryptor = %d, mem = %x\n", descriptor, mem);

    printf("Commands: \nr - receive message \ns - send message (s \"Your text\")\nq - quit chat\n");

    printf("Please enter your user id (1 or 2):\n");
    int user_id = 0;
    scanf("%d", &user_id);

    if (user_id == 1) {
        mem_to_send = mem;
        mem_to_receive = mem + 1000;
    } 
    else {
        mem_to_send = mem + 1000;
        mem_to_receive = mem;
    }

    while(1) {
        scanf("%c", &command);
        if (command == 'r') {
            strcpy(msg, mem_to_receive);

            // Deleting readed memory
            int msg_len = strlen(msg);
            for (int i = 0; i < msg_len; i++)
                mem_to_receive[i] = '\0';
            
            printf("Received message:\n");
            printf("%s\n", msg);
        }
        else if (command == 's') {
            int i = 0;
            scanf("%c", &command);
            while (i < 998 && (result = scanf("%c", msg + i)) > 0 && msg[i] != '\n') i++;
            msg[i] = '\n';
            msg[i] = '\0';
            printf("Sending message...\n");
            strcat(mem_to_send, msg);
        }
        else if (command == 'q') {
            break;
        }
    }
    shmdt(mem);
    printf("Good bye!\n");
    return 0;
}


void OpenSharedMemory(const char* path, char** mem_ret, int* descriptor_ret) {    
    umask(0);
    char* mem;
    int key = ftok(path, 0);
    int descriptor = shmget(key, sizeof(char) * size_of_bufer, 0666 | IPC_CREAT | IPC_EXCL);

    if (descriptor >= 0) {                                                              // New shared memory
        mem = (char*) shmat(descriptor, NULL, 0);
        for (int i = 0; i < size_of_bufer; i++) {
            mem[i] = 0;
        }
    }
    else {                                                                              // If shared memory exists  
        descriptor = shmget(key, sizeof(char) * size_of_bufer, 0);
        mem = (char*) shmat(descriptor, NULL, 0);
    }
    *mem_ret = mem;
    *descriptor_ret = descriptor;
}