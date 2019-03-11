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
void fFlagOutput(PAGETABLE *pt, string fileName, int addressSizeUsed);

int main(int argc, char *argv[]) {
    int argumentCount = 1;
    int nFlag = 0;
    int tFlag = 0;
    int fFlag = 0;
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
                fFlag = 1;
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
    int addressSizeUsed = 0;
    for (int i = 0; argumentCount < argc; i++) {
        pageTableSizes[i] = atoi(argv[argumentCount++]);
        addressSizeUsed += pageTableSizes[i];
    }
    //TODO:: Check Address Size
    PAGETABLE pagetable(levelCount, pageTableSizes);
    if ((filePointer = fopen(inputFileName.c_str(), "rb")) == NULL) {
        fprintf(stderr, "Can not open %s for reading\n", inputFileName.c_str());
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
    if(fFlag){
        fFlagOutput(&pagetable, outputFileName, addressSizeUsed);
    }
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

void fFlagOutput(PAGETABLE *pt, string fileName, int addressSizeUsed){
    FILE *filePointer;
    if ((filePointer = fopen(fileName.c_str(), "w")) == nullptr) {
        fprintf(stderr, "Can not open %s for writing\n", fileName.c_str());
        exit(FILE_OPEN_ERROR);
    }
    int maxPageTableSize = 1 << addressSizeUsed;
    //Initialize bool flag array to 0
    bool *framesOutputed = new bool[maxPageTableSize];
    for(int i = 0; i < maxPageTableSize; i++){
        framesOutputed[i] = false;
    }
    int offset = pt->levelShiftArray[pt->levelCount - 1];
    int frameNumber;
    int pageNumber;
    for(int i = 0; i < maxPageTableSize; i++){
        pageNumber = i << offset;
        frameNumber = pt->getFrameNumber(pageNumber);
        if(frameNumber != INVALID){
            if(!framesOutputed[frameNumber]) {
                fprintf(filePointer, "%08X -> %08X\n", i, frameNumber);
                framesOutputed[frameNumber] = true;
            }
        }

    }
    delete[] framesOutputed;
    fclose(filePointer);

}
