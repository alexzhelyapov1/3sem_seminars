// Compile with: g++ thread.cpp -pthread

// Theory:
//          pthread_create
//          pthread_join

#include <stdio.h>
#include <pthread.h>

int number_of_threads = 0;

void *my_func(void *arg) {
    printf("I am new thread = %ld\n", pthread_self());
    number_of_threads++;
    return NULL;
}

int main() {
    printf("I am first thread = %ld\n", pthread_self());
    number_of_threads++;

    pthread_t thread = 777;
    for (int i = 0; i < 5; i++) {
    if (pthread_create(&thread, NULL, my_func, NULL))
        printf("Error! Thread did not create\n");
        pthread_join(thread, NULL);
        printf("Threads synchronized\n");
    }
    printf("Sum number of threads = %d\n", number_of_threads);
    return 0;
}