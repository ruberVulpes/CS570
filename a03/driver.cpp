//
// Created by William Fox on 2019-03-06.
//
#define HIT 0
#define MISS 1
#define FILE_OPEN_ERROR 2

#include "unistd.h"
#include "byutr.h"
#include "page_table.h"


#include <stdlib.h>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;
int pageInsert(PAGETABLE * pt, unsigned int logicalAddr, unsigned int frame);
int main(int argc, char *argv[]){
    int argumentCount = 1;
    int nFlag = 0;
    int tFlag = 0;
    string inputFileName;
    string outputFileName;

    FILE *filePointer;
    int traceLimit = 0;
    p2AddrTr currentTrace;

    unsigned int hits = 0;
    unsigned int misses = 0;
    int option = 0;
    while ((option = getopt(argc, argv, "n:f:t")) != -1) {
        switch (option) {
            case 'n' :
                nFlag = 1;
                traceLimit = atoi(optarg);
                argumentCount += 2;
                break;
            case 'f' :
                outputFileName = string(optarg);
                argumentCount += 2;
                break;
            case 't' :
                tFlag = 1;
                argumentCount++;
                break;
            default:
                break;
        }
    }
    inputFileName = argv[argumentCount++];
    int levelCount = argc - argumentCount;
    int pageTableSizes[levelCount];
    for (int i = 0; argumentCount < argc; i++) {
        pageTableSizes[i] = atoi(argv[argumentCount++]);
    }
    PAGETABLE pagetable(levelCount, pageTableSizes);
    if((filePointer = fopen(inputFileName.c_str(), "rb"))== NULL){
        fprintf(stderr, "Can not open file for reading\n");
        exit(FILE_OPEN_ERROR);
    }
    while(!feof(filePointer)){
        if(NextAddress(filePointer, &currentTrace)){
            if(pageInsert(&pagetable, currentTrace.addr, misses)){
                misses++;
            } else {
                hits++;
            }
        } else {
            break;
//            fprintf(stderr, "Unable to get next trace %d \n", hits + misses);
//            exit(GET_NEXT_TRACE_ERROR);
        }
        if(traceLimit <= hits + misses && nFlag == 1){
            break;
        }
    }
    cout << hits << " " << misses << " " << pagetable.sizeTotal() << endl;

    return 0;
}
int pageInsert(PAGETABLE * pt, unsigned int logicalAddr, unsigned int frame){
    if(pt->insert(logicalAddr, frame)){
        return MISS;
    } else {
        return HIT;
    }
}

