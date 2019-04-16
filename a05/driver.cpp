//
// Created by William Fox on 4/7/2019.
// cssc1084
//
#define FROG_LIMIT 3
#define BELT_LIMIT 10
#define CANDIE_LIMIT 100

#define LUCY thread_args[1]
#define ETHEL thread_args[0]
#define FROG_BITE thread_args[2]
#define FROG 0
#define SNAIL_SUCKER thread_args[3]
#define SNAIL 1

#include "driver.h"

using namespace std;

int main(int argc, char *argv[]) {

    sem_init(&frog_limit, 0, FROG_LIMIT);
    sem_init(&belt_limit, 0, BELT_LIMIT);
    sem_init(&belt_candies, 0, 0);
    sem_init(&belt_mutex, 0, 1);
    sem_init(&produce_limit, 0, CANDIE_LIMIT);
    sem_init(&consume_limit, 0, CANDIE_LIMIT);

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
    //Initialize Arguments that will be passed to the threads
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
    //Create Consumer Threads
    for (int i = 0; i < 2; ++i) {
        pthread_create(&threads[i], nullptr, &consumer,
                       (void *) &thread_args[i]);
    }
    //Create Producer Threads
    for (int i = 2; i < 4; ++i) {
        pthread_create(&threads[i], nullptr, &producer,
                       (void *) &thread_args[i]);
    }
    // Join All Threads
    for (auto &thread : threads) {
        pthread_join(thread, nullptr);
    }
    //Cleanup Semaphores
    sem_destroy(&frog_limit);
    sem_destroy(&belt_limit);
    sem_destroy(&belt_candies);
    sem_destroy(&belt_mutex);
    sem_destroy(&produce_limit);
    sem_destroy(&consume_limit);
    driver_print_helper();

}

// Print Production Report
void driver_print_helper() {
    cout << endl << "PRODUCTION REPORT" << endl;
    cout << "----------------------------------------";
    cout << endl << "Crunchy Frog Bite Producer Generated ";
    cout << FROG_BITE.produced << " Candies" << endl;
    cout << "Everlasting Escargot Sucker Producer Generated ";
    cout << SNAIL_SUCKER.produced << " Candies" << endl;
    cout << "Lucy Consumed " << LUCY.consumed[FROG];
    cout << " Crunchy Frog Bites + " << LUCY.consumed[SNAIL];
    cout << " Everlasting Escargot Suckers = ";
    cout << LUCY.consumed[FROG] + LUCY.consumed[SNAIL] << endl;
    cout << "Ethel Consumed " << ETHEL.consumed[FROG];
    cout << " Crunchy Frog Bites + " << ETHEL.consumed[SNAIL];
    cout << " Everlasting Escargot Suckers = ";
    cout << ETHEL.consumed[FROG] + ETHEL.consumed[SNAIL] << endl;
}