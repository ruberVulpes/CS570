//
// Created by William Fox on 4/7/2019.
// cssc1084
//

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

    // Print Production Report
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

//Used for every consumption/production of candy
void print_helper() {
    int frog_count = FROG_BITE.produced;
    frog_count -= (ETHEL.consumed[FROG] + LUCY.consumed[FROG]);
    int snail_count = SNAIL_SUCKER.produced;
    snail_count -= (ETHEL.consumed[SNAIL] + LUCY.consumed[SNAIL]);
    int produced_count = FROG_BITE.produced + SNAIL_SUCKER.produced;
    cout << "Belt: " << frog_count << " frogs + ";
    cout << snail_count << " escargots = ";
    cout << frog_count + snail_count << " produced: " << produced_count;
}

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
        print_helper();
        cout << "\tAdded " << *arguments->name << "." << endl;
        sem_post(arguments->belt_mutex);
        sem_post(arguments->belt_candies);
        //Sleep if wait time specified, default is 0
        //Convert ms to micro seconds
        usleep(arguments->wait_time * 1000);
    }
}

void *consumer(void *data) {
    args *arguments = (args *) data;
    arguments->consumed[FROG] = 0;
    arguments->consumed[SNAIL] = 0;
    while (true) {
        //Exit if consume limit has been hit
        if (sem_trywait(arguments->consume_limit) == -1) {
            pthread_exit(nullptr);
        }
        sem_wait(arguments->belt_candies);
        sem_wait(arguments->belt_mutex);
        if (arguments->belt[*arguments->head] == "Crunchy Frog Bite") {
            sem_post(arguments->frog_limit);
            arguments->consumed[FROG]++;
        } else {
            arguments->consumed[SNAIL]++;
        }
        print_helper();
        cout << "\t" << *arguments->name << " consumed ";
        cout << arguments->belt[*arguments->head] << "." << endl;
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


