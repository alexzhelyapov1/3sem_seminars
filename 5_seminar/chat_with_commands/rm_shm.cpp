#include "chat.h"

int main() {
    const char* path_mine1 = "~/Desktop/root/infa/3sem_seminars/5_seminar/chat_with_commands/chat.cpp";

    umask(0);
    int key = ftok(path_mine1, 0);
    int descriptor = shmget(key, sizeof(char) * size_of_bufer, 0666 | IPC_CREAT | IPC_EXCL);

    if (descriptor < 0) {
        printf("Memory exists. Deleting...\n");
        descriptor = shmget(key, sizeof(int) * 3, 0);
        shmctl(descriptor, IPC_RMID, NULL);
        printf("Deleted successfully!\n");
    }
    return 0;
}