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
#include <iomanip>

using namespace std;

int pageInsert(PAGETABLE *pt, unsigned int logicalAddr, unsigned int frame);

void printHelper(int size, int hits, int missess, int pageSize);

int getFrame(PAGETABLE *pt, unsigned int logicalAddr);

int getPhysicalAddr(PAGETABLE *pt, unsigned int logicalAddr);

void tFlagPrint(PAGETABLE *pt, unsigned int logicalAddress);

int main(int argc, char *argv[]) {
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
    if ((filePointer = fopen(inputFileName.c_str(), "rb")) == NULL) {
        fprintf(stderr, "Can not open file for reading\n");
        exit(FILE_OPEN_ERROR);
    }
    while (!feof(filePointer)) {
        if (NextAddress(filePointer, &currentTrace)) {
            if (pageInsert(&pagetable, currentTrace.addr, misses)) {
                misses++;

            } else {
                hits++;
            }
            if (tFlag) {
                tFlagPrint(&pagetable, (unsigned int)currentTrace.addr);
            }
        } else {
            break;
        }
        if (traceLimit <= hits + misses && nFlag == 1) {
            break;
        }
    }
    fclose(filePointer);
    int pageSize = pagetable.entryCountArray[levelCount];
    printHelper(pagetable.sizeTotal(), hits, misses, pageSize);
}

int pageInsert(PAGETABLE *pt, unsigned int logicalAddr, unsigned int frame) {
    if (pt->insert(logicalAddr, frame)) {
        return MISS;
    } else {
        return HIT;
    }
}

int getFrame(PAGETABLE *pt, unsigned int logicalAddr) {
    return pt->getFrameNumber(logicalAddr);
}

int getPhysicalAddr(PAGETABLE *pt, unsigned int logicalAddr) {
    int frameNumber = getFrame(pt, logicalAddr);
    //Frame Number * Page Size
    int startingLocation = frameNumber * pt->entryCountArray[pt->levelCount];
    int bitmask = pt->levelBitmaskArray[pt->levelCount];
    int offset = logicalAddr & bitmask;
    return startingLocation + offset;
}

void printHelper(int size, int hits, int missess, int pageSize) {
    double total = hits + missess;
    cout << "Page table size: " << pageSize << endl;
    cout << setprecision(4) << "Hits " << hits << " (" << hits / total * 100;
    cout << "%), Misses " << missess << " (" << missess / total * 100 << "%) ";
    cout << setprecision(100) << "# Addressess " << total << endl;
    cout << "Bytes used: " << size << endl;
}

void tFlagPrint(PAGETABLE *pt, unsigned int logicalAddress) {
    int physicalAddress = getPhysicalAddr(pt, logicalAddress);
    printf("%08X -> %08X\n", logicalAddress, physicalAddress);
}

