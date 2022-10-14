// Theory part
// --------------------------------------------------------------------------------------------------------------------
// We want to use semaphors from linux:
// -ftok();
// -semget(key, number of semaphores, flags);
// -semop(semid(returned be semget), hs, number of sems we want to work (len of struct array))

// out realisation:
// v(s) = {s++}
// p(s) = {while s == 0 block; s--}        pause

// A(s, n) = {s += n}                      // sem_op > 0 and abs = n
// D(s, n) = {while s < n block; s-=n}     // sem_op < 0 and abs = n
// Z(s) = {while s > 0 block}              // sem_op = 0

// For doing operations with semaphors we need to give struct array {3, 8, 0}, {7, 5, 0}, {9, 0, 0} - doing 3 activities
// --------------------------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>


int main() {
    const char* path= "~/Desktop/root/infa/3sem_seminars/7_seminar/smph.cpp";
    struct sembaf* my_sembaf = NULL;

    return 0;
}