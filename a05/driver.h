//
// Created by William Fox on 4/7/2019.
//

#ifndef CS570_DRIVER_H
#define CS570_DRIVER_H

#include <unistd.h>
#include <semaphore.h>
#include <string>
#include <iostream>

using namespace std;

int option = 0;
int flagValues[4] = {0, 0, 0, 0};

sem_t *conveyor_belt_mutex;
sem_t *crunchy_frog_bite_limit;
sem_t *conveyor_belt_size;
string conveyor_belt[10];
int head = 0;
int tail = 0;

struct thread_args {
    sem_t * cbm = conveyor_belt_mutex;
    sem_t *cfbt = crunchy_frog_bite_limit;
    sem_t *cbs = conveyor_belt_size;
    string *cb = conveyor_belt;
    int *start = &head;
    int *end = &tail;
    string *name;
    int time_to_wait;
};
string thread_names[4] = {"Ethel", "Lucy", "Crunchy Frog Bite", "Everlasting Escargot Sucker"};
pthread_t threads[4];
void *producer(void *);
void producer_helper(sem_t * mutex_ptr, sem_t *frog_bite_limit_ptr, sem_t *conveyor_belt_size_ptr, string conveyor_belt_ptr[10], int* tail, string candie, int time_to_produce);
#endif //CS570_DRIVER_H
