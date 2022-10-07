// Compile with: g++ thread.cpp -pthread

// Theory:
//          pthread_create
//          pthread_join

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int number_of_threads = 0;

void *my_func(void *arg) {
    printf("I am new thread = %ld\n", pthread_self());
    number_of_threads++;
    sleep(1);
    return NULL;
}

int main() {
    printf("I am first thread = %ld\n", pthread_self());
    number_of_threads++;

    pthread_t thread[10];
    for (int i = 0; i < 5; i++) {
        if (pthread_create(thread + i, NULL, my_func, NULL))
            printf("Error! Thread did not create\n");
    }
    for (int i = 0; i < 5; i++) {
        pthread_join(thread[i], NULL);
        printf("Thread %ld synchronized\n", thread[i]);
    }
    printf("Sum number of threads = %d\n", number_of_threads);
    return 0;
}