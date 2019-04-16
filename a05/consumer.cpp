//
// Created by William Fox on 2019-04-16.
//

#include "consumer.h"

void *consumer(void *data) {
    args *arguments = (args *) data;
    arguments->consumed[FROG] = 0;
    arguments->consumed[SNAIL] = 0;
    while (true) {
        //Exit if consume limit has been hit
        if (sem_trywait(arguments->consume_limit) == -1) {
            pthread_exit(NULL);
        }
        sem_wait(arguments->belt_candies);
        sem_wait(arguments->belt_mutex);
        if (arguments->belt[*arguments->head] == "Crunchy Frog Bite") {
            sem_post(arguments->frog_limit);
            arguments->consumed[FROG]++;
        } else {
            arguments->consumed[SNAIL]++;
        }
        consumer_print_helper(arguments);
        //Clear current candy string
        arguments->belt[*arguments->head] = "";
        //Increase head counter of the circular array
        *arguments->head = (*arguments->head + 1) % BELT_LIMIT;
        sem_post(arguments->belt_mutex);
        sem_post(arguments->belt_limit);
        //Wait if required, wait time is default to 0
        //Convert ms to micro seconds
        usleep(arguments->wait_time * 1000);
    }
}

void consumer_print_helper(args *arguments) {
    int frog_count = FROG_BITE.produced;
    frog_count -= (ETHEL.consumed[FROG] + LUCY.consumed[FROG]);
    int snail_count = SNAIL_SUCKER.produced;
    snail_count -= (ETHEL.consumed[SNAIL] + LUCY.consumed[SNAIL]);
    int produced_count = FROG_BITE.produced + SNAIL_SUCKER.produced;
    cout << "Belt: " << frog_count << " frogs + ";
    cout << snail_count << " escargots = ";
    cout << frog_count + snail_count << " produced: " << produced_count;
    cout << "\t" << *arguments->name << " consumed ";
    cout << arguments->belt[*arguments->head] << "." << endl;
}
