//
// Created by William Fox on 4/7/2019.
//

#include "driver.h"
#include <errno.h>

using namespace std;

int main(int argc, char *argv[]) {

    sem_t *conveyor_belt_mutex;
    sem_t *crunchy_frog_bite_limit;
    sem_t *conveyor_belt_size;
//    sem_init(&crunchy_frog_bite_limit, 0, 3);
//    sem_init(&conveyor_belt_mutex, 0, 1);
#define SHAREDSEM "Test"
    sem_unlink(SHAREDSEM);
    conveyor_belt_size = sem_open("Test", O_CREAT, 0600, 10);
    if(conveyor_belt_size == SEM_FAILED)
        cout << strerror(errno);
    int * value;

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
    thread_args frog;
    frog.name = &thread_names[2];
    int th_rt[5];
    for (int i = 0; i < 4; ++i) {
        th_rt[i] = pthread_create(&threads[i], NULL, producer, (void *) &frog);
    }
    for (int i = 0; i < 4; ++i) {
        pthread_join(threads[i], NULL);
    }
//    producer(&conveyor_belt_mutex, &crunchy_frog_bite_limit, &conveyor_belt_size, conveyor_belt, &tail, thread_names[2], 0);
//    producer(&conveyor_belt_mutex, &crunchy_frog_bite_limit, &conveyor_belt_size, conveyor_belt, &tail, thread_names[2], 0);
    sem_unlink(SHAREDSEM);
}

void *producer(void *arguments) {
    thread_args *args = (thread_args *) arguments;
    producer_helper(args->cbm, args->cfbt, args->cbs, args->cb, args->start, *args->name, args->time_to_wait);
}

void producer_helper(sem_t *mutex_ptr, sem_t *frog_bite_limit_ptr, sem_t *conveyor_belt_size_ptr,
                     string conveyor_belt_ptr[10], int *tail, string candie, int time_to_produce) {
    if (candie == "Everlasting Escargot Sucker") {
        sem_wait(frog_bite_limit_ptr);
    }
    sem_wait(conveyor_belt_size_ptr);
    sem_wait(mutex_ptr);
    conveyor_belt_ptr[(*tail)++] = candie;
    *tail %= 10;
    sem_post(mutex_ptr);

}