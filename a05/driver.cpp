//
// Created by William Fox on 4/7/2019.
//

#include "driver.h"
#include <errno.h>

using namespace std;
struct pck {
    sem_t *limit;
    sem_t *mutex;
    int n;
    int *m;
};

int main(int argc, char *argv[]) {

//   sem_t conveyor_belt_mutex;
//    sem_t crunchy_frog_bite_limit;
//    sem_t conveyor_belt_size;
    sem_init(&crunchy_frog_bite_limit, 0, 3);
    sem_init(&conveyor_belt_mutex, 0, 1);
    int *value;
    sem_getvalue(&crunchy_frog_bite_limit, value);
    cout << *value << endl;
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
//   pck pack;
//   pack.limit = &crunchy_frog_bite_limit;
   pck packs[4];
   for(int i = 0; i < 4; ++i){
       packs[i].limit = &crunchy_frog_bite_limit;
       packs[i].mutex = &conveyor_belt_mutex;
       packs[i].n = i + 1;
       packs[i].m = value;
       pthread_create(&threads[i],  NULL, &worker, (void*)&packs[i]);
   }
   for(int i =0; i < 4; ++i){
      pthread_join(threads[i], 0);
   }
   sem_destroy(&crunchy_frog_bite_limit);
   sem_destroy(&conveyor_belt_mutex);

}

void *worker(void *args){
	pck *pack = (pck *) args;
//        cout << "Thread: " << pack->n << " waiting" << endl;
        sem_wait(pack->mutex);
	//sem_wait(pack->limit);
	cout << "Thread: " << pack->n << " in: " << *pack->m << endl;
        *(pack->m) *= pack->n;
	//sem_post(pack->limit);
	sem_post(pack->mutex);        
//	cout << "Thread: " << pack->n << " released" << endl;
}
