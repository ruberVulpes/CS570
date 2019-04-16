//
// Created by William Fox on 4/7/2019.
//

#ifndef CS570_DRIVER_H
#define CS570_DRIVER_H

#include <unistd.h>
#include <semaphore.h>
#include <unistd.h>
#include <string>
#include <iostream>

#define FROG_LIMIT 3
#define BELT_LIMIT 10
#define CANDIE_LIMIT 100

#define LUCY thread_args[1]
#define ETHEL thread_args[0]
#define FROG_BITE thread_args[2]
#define FROG 0
#define SNAIL_SUCKER thread_args[3]
#define SNAIL 1
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

int option = 0;
int flagValues[4] = {0, 0, 0, 0};

sem_t belt_mutex;
sem_t frog_limit;
sem_t belt_limit;
sem_t belt_candies;
sem_t produce_limit;
sem_t consume_limit;
string conveyor_belt[10];
int head = 0;
int tail = 0;

string thread_names[4] = {"Ethel", "Lucy",
                          "Crunchy Frog Bite", "Everlasting Escargot Sucker"};
pthread_t threads[4];
args thread_args[4];


void print_helper();

void *producer(void *data);

void *consumer(void *data);

#endif //CS570_DRIVER_H
