//
// Created by William Fox on 2019-02-27.
//
#include <pthread.h>
#include <stdio.h>

#include "worker.h"

int main() {
    pthread_t threads[5];
    int values[] = {0, 1, 2, 3, 4};
    int thread_returns[5];
    int i;
    for (i = 0; i < 5; i++) {
        thread_returns[i] = pthread_create(&threads[i], NULL, (void *)&worker, (void *) &values[i]);
    }
    for(i = 0; i < 5; i++){
        pthread_join(threads[i], (void *) &thread_returns[i]);

    }
    printf("work completed.\n");

}

