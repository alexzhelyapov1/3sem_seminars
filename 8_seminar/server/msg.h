#ifndef MSG_H
#define MSG_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <time.h>

const char* path = "/home/alexey_zhelyapov/Desktop/root/infa/3sem_seminars/8_seminar/msg.h";
// const char* path = "/home/leksey2/3sem_seminars/8_seminar/msg.h";

struct msg_struct {
    long type;
    int from;       // from who
    int to;         // to who
    char data[1000];
};

const int size_of_info = 50;

#endif