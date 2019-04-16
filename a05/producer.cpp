//
// Created by William Fox on 2019-04-16.
//

#include "producer.h"

void *producer(void *data) {
    args *arguments = (args *) data;
    arguments->produced = 0;
    while (true) {
        //Exit if produce limit has been hit
        if (sem_trywait(arguments->produce_limit) == -1) {
            pthread_exit(nullptr);
        }
        if (*arguments->name == "Crunchy Frog Bite") {
            sem_wait(arguments->frog_limit);
        }
        sem_wait(arguments->belt_limit);
        sem_wait(arguments->belt_mutex);
        arguments->belt[*arguments->tail] = *arguments->name;
        arguments->produced++;
        //Increase tail counter of circular array
        *arguments->tail = (*arguments->tail + 1) % BELT_LIMIT;
        producer_print_helper(arguments);
        sem_post(arguments->belt_mutex);
        sem_post(arguments->belt_candies);
        //Sleep if wait time specified, default is 0
        //Convert ms to micro seconds
        usleep(arguments->wait_time * 1000);
    }
}

void producer_print_helper(args *arguments) {
    int frog_count = FROG_BITE.produced;
    frog_count -= (ETHEL.consumed[FROG] + LUCY.consumed[FROG]);
    int snail_count = SNAIL_SUCKER.produced;
    snail_count -= (ETHEL.consumed[SNAIL] + LUCY.consumed[SNAIL]);
    int produced_count = FROG_BITE.produced + SNAIL_SUCKER.produced;
    cout << "Belt: " << frog_count << " frogs + ";
    cout << snail_count << " escargots = ";
    cout << frog_count + snail_count << " produced: " << produced_count;
    cout << "\tAdded " << *arguments->name << "." << endl;
}