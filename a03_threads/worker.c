//
// Created by William Fox on 2019-02-27.
//
#include <stdio.h>

void worker(void *value) {
    int *number = (int *) value;
    printf("%d\n", *number * *number);
}