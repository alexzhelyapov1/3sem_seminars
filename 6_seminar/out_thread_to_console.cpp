// Compile with: g++ thread.cpp -pthread

#include <stdio.h>
#include <pthread.h>

int main() {
    printf("Id of current thread = %ld\n", pthread_self());
    return 0;
}