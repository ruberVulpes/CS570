//
// Created by William Fox on 2019-02-27.
//
#include <pthread.h>
#include <stdio.h>

#include "worker.h"

int main() {
    pthread_t threads[4];
    int thread_returns[4];
    int i;
    for (i = 0; i < 5; i++) {
        thread_returns[i] = pthread_create(&threads[i], NULL, (void *)&worker, (void *) &i);
    }
    for(i = 0; i < 5; i++){
        pthread_join(threads[i], NULL);
    }
    printf("work completed.\n");

}

