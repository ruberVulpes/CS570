//
// Created by William Fox on 2019-04-16.
//

#ifndef CS570_ARGS_H
#define CS570_ARGS_H
#include <semaphore.h>
#include <string>
using namespace std;
struct args {
    sem_t *belt_mutex;
    sem_t *frog_limit;
    sem_t *belt_limit;
    sem_t *belt_candies;
    sem_t *produce_limit;
    sem_t *consume_limit;

    string *belt;
    int *head;
    int *tail;
    int wait_time;
    int produced;
    string *name;
    int consumed[2];
};

#endif //CS570_ARGS_H
