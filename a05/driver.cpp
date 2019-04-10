//
// Created by William Fox on 4/7/2019.
//

#include "driver.h"
#include <errno.h>

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
    string *name;
};

int main(int argc, char *argv[]) {

    sem_init(&frog_limit, 0, 3);
    sem_init(&belt_limit, 0, 10);
    sem_init(&belt_candies, 0, 0);
    sem_init(&belt_mutex, 0, 1);
    sem_init(&produce_limit, 0, 10);
    sem_init(&consume_limit, 0, 10);

    char *end;
    while ((option = getopt(argc, argv, "E:L:f:e:")) != -1) {
        switch (option) {
            case 'E' :
                flagValues[0] = strtol(optarg, &end, 10);
                break;
            case 'L' :
                flagValues[1] = strtol(optarg, &end, 10);
                break;
            case 'f' :
                flagValues[2] = strtol(optarg, &end, 10);
                break;
            case 'e':
                flagValues[3] = strtol(optarg, &end, 10);
                break;
            default:
                break;
        }
    }
    args thread_args[4];
    for (int i = 0; i < 4; ++i) {
        thread_args[i].frog_limit = &frog_limit;
        thread_args[i].belt_limit = &belt_limit;
        thread_args[i].belt_mutex = &belt_mutex;
        thread_args[i].belt_candies = &belt_candies;
        thread_args[i].produce_limit = &produce_limit;
        thread_args[i].consume_limit = &consume_limit;

        thread_args[i].belt = conveyor_belt;
        thread_args[i].head = &head;
        thread_args[i].tail = &tail;
        thread_args[i].wait_time = flagValues[i];
        thread_args[i].name = &thread_names[i];
    }
    for (int i = 0; i < 2; ++i) {
        pthread_create(&threads[i], nullptr, &consumer, (void *) &thread_args[i]);
    }
    for (int i = 2; i < 4; ++i) {
        pthread_create(&threads[i], nullptr, &producer, (void *) &thread_args[i]);
    }
    for (int i = 0; i < 4; ++i) {
        pthread_join(threads[i], 0);
    }
    sem_destroy(&frog_limit);
    sem_destroy(&belt_limit);
    sem_destroy(&belt_candies);
    sem_destroy(&belt_mutex);
    sem_destroy(&produce_limit);
    sem_destroy(&consume_limit);

}

void *producer(void *data) {
    args *arguments = (args *) data;

    while(true) {
        if (sem_trywait(arguments->produce_limit) == -1) {
            pthread_exit(nullptr);
        }
        if (*arguments->name == "Crunchy Frog Bite") {
            sem_wait(arguments->frog_limit);
        }
        sem_wait(arguments->belt_limit);
        sem_wait(arguments->belt_mutex);
        arguments->belt[*arguments->tail] = *arguments->name;
        cout << arguments->belt[*arguments->tail] << " added" << endl;
        *arguments->tail = (*arguments->tail + 1) % 10;
        sem_post(arguments->belt_mutex);
        sem_post(arguments->belt_candies);
        //wait
    }
}

void *consumer(void *data) {
    args *arguments = (args *) data;
    while (true) {
        if (sem_trywait(arguments->consume_limit) == -1) {
            pthread_exit(nullptr);
        }
        sem_wait(arguments->belt_candies);
        sem_wait(arguments->belt_mutex);
        if (arguments->belt[*arguments->head] == "Crunchy Frog Bite") {
            sem_post(arguments->frog_limit);
        }
        cout << arguments->belt[*arguments->head] << " Removed by " << *arguments->name << endl;
        arguments->belt[*arguments->head] = "";
        *arguments->head = (*arguments->head + 1) % 10;
        sem_post(arguments->belt_mutex);
        sem_post(arguments->belt_limit);
    }
}


