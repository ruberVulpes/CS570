//
// Created by William Fox on 4/7/2019.
//

#include "driver.h"
#include <errno.h>

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
        pthread_join(threads[i], nullptr);
    }
    sem_destroy(&frog_limit);
    sem_destroy(&belt_limit);
    sem_destroy(&belt_candies);
    sem_destroy(&belt_mutex);
    sem_destroy(&produce_limit);
    sem_destroy(&consume_limit);

    cout << endl << "Crunchy Frog Bite Producer Generated " << thread_args[2].produced << " Candies" << endl;
    cout << "Everlasting Escargot Sucker Producer Generated " << thread_args[3].produced << " Candies" << endl;
    cout << "Lucy Consumed " << thread_args[1].consumed[0] << " Crunchy Frog Bites + ";
    cout << thread_args[1].consumed[1] << " Everlasting Escargot Suckers = "
         << thread_args[1].consumed[0] + thread_args[1].consumed[1]
         << endl;
    cout << "Ethel Consumed " << thread_args[0].consumed[0] << " Crunchy Frog Bites + ";
    cout << thread_args[0].consumed[1] << " Everlasting Escargot Suckers = "
         << thread_args[0].consumed[0] + thread_args[0].consumed[1]
         << endl;
}

void print_helper() {
    int frog_count = thread_args[2].produced - thread_args[0].consumed[0] - thread_args[1].consumed[0];
    int snail_count = thread_args[3].produced - thread_args[0].consumed[1] - thread_args[1].consumed[1];
    int produced_count = thread_args[2].produced + thread_args[3].produced;

    cout << "Belt: " << frog_count << " frogs + ";
    cout << snail_count << " escargots = ";
    cout << frog_count + snail_count << " produced: " << produced_count;
}

void *producer(void *data) {
    args *arguments = (args *) data;
    arguments->produced = 0;
    while (true) {
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
        *arguments->tail = (*arguments->tail + 1) % BELT_LIMIT;
        print_helper();
        cout << "\tAdded " << *arguments->name << "." << endl;
        sem_post(arguments->belt_mutex);
        sem_post(arguments->belt_candies);
        usleep(arguments->wait_time * 1000);
    }
}

void *consumer(void *data) {
    args *arguments = (args *) data;
    arguments->consumed[0] = 0;
    arguments->consumed[1] = 0;
    while (true) {
        if (sem_trywait(arguments->consume_limit) == -1) {
            pthread_exit(nullptr);
        }
        sem_wait(arguments->belt_candies);
        sem_wait(arguments->belt_mutex);
        if (arguments->belt[*arguments->head] == "Crunchy Frog Bite") {
            sem_post(arguments->frog_limit);
            arguments->consumed[0]++;
        } else {
            arguments->consumed[1]++;
        }
	print_helper();
        cout << "\t" << *arguments->name << " consumed " << arguments->belt[*arguments->head] << "." << endl;
        arguments->belt[*arguments->head] = "";
        *arguments->head = (*arguments->head + 1) % BELT_LIMIT;
	sem_post(arguments->belt_mutex);
        sem_post(arguments->belt_limit);
        usleep(arguments->wait_time * 1000);
    }
}


