//
// Created by William Fox on 4/7/2019.
// cssc1084
//

#ifndef CS570_DRIVER_H
#define CS570_DRIVER_H

#include <unistd.h>
#include <semaphore.h>
#include <unistd.h>
#include <errno.h>
#include <string>
#include <iostream>

#include "producer.h"
#include "consumer.h"
#include "args.h"

using namespace std;

int option = 0;
int flagValues[4] = {0, 0, 0, 0};

sem_t belt_mutex;
sem_t frog_limit;
sem_t belt_limit;
sem_t belt_candies;
sem_t produce_limit;
sem_t consume_limit;
//Treated as circular array
string conveyor_belt[10];
int head = 0;
int tail = 0;

string thread_names[4] = {"Ethel", "Lucy",
                          "Crunchy Frog Bite", "Everlasting Escargot Sucker"};
pthread_t threads[4];
args thread_args[4];


void driver_print_helper();


#endif //CS570_DRIVER_H
