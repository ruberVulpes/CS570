//
// Created by William Fox on 2019-03-06.
//
#define HIT 0
#define MISS 1
#define FILE_OPEN_ERROR 2
#define ADDRESS_SIZE_ERROR 3

#include "unistd.h"
#include "byutr.h"
#include "page_table.h"


#include <stdlib.h>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>

using namespace std;

//Inserts into Page Table, returns Hit/Miss
int pageInsert(PAGETABLE *pagetable, unsigned int logicalAddr, unsigned int frame);

//Helper for output statistics printing
void printHelper(int size, int hits, int missess, unsigned int pageSize);

//Returns frame number for the specified logical address
int getFrame(PAGETABLE *pagetable, unsigned int logicalAddr);

//Returns physical address for specified logical address
int getPhysicalAddr(PAGETABLE *pagetable, unsigned int logicalAddr);

//Helps handle tFlag case, prints Logical -> Physical
void tFlagHelper(PAGETABLE *pagetable, unsigned int logicalAddress, bool tFlag);

//Helps handle pFlag case, outputs all Page Number -> Frame Number
void pFlagHelper(PAGETABLE *pt, string file, int addressSizeUsed, bool pFlag);

int main(int argc, char *argv[]) {
    //argv[0] is pagetable so argc will always start at 1
    int argumentCount = 1;
    bool nFlag = false;
    bool tFlag = false;
    bool pFlag = false;
    string inputFileName;
    string outputFileName;

    FILE *filePointer;
    int traceLimit = 0;
    p2AddrTr currentTrace;

    unsigned int hits = 0;
    unsigned int misses = 0;
    int option = 0;
    while ((option = getopt(argc, argv, "n:p:t")) != -1) {
        switch (option) {
            case 'n' :
                nFlag = true;
                traceLimit = atoi(optarg);
                argumentCount += 2;
                break;
            case 'p' :
                pFlag = true;
                outputFileName = string(optarg);
                argumentCount += 2;
                break;
            case 't' :
                tFlag = true;
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
    //Inputed address validation
    if (addressSizeUsed > ADDRESS_SIZE) {
        fprintf(stderr, "Page Level Size(s) Exceed 32bit Address Size\n");
        exit(ADDRESS_SIZE_ERROR);
    } else if (addressSizeUsed == 0) {
        fprintf(stderr, "Please specify Page Level Size(s)\n");
        exit(ADDRESS_SIZE_ERROR);
    }
    PAGETABLE pagetable(levelCount, pageTableSizes);
    if ((filePointer = fopen(inputFileName.c_str(), "rb")) == nullptr) {
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
            tFlagHelper(&pagetable, (unsigned int) currentTrace.addr, tFlag);
        }
        //End if nFlag limit is hit (misses + hits = addressesProcessed)
        if (traceLimit <= hits + misses && nFlag) {
            break;
        }
    }
    fclose(filePointer);

    pFlagHelper(&pagetable, outputFileName, addressSizeUsed, pFlag);

    unsigned pageSize = pagetable.entryCountArray[levelCount];
    printHelper(pagetable.sizeTotal(), hits, misses, pageSize);
}

int pageInsert(PAGETABLE *pagetable, unsigned int logicalAddr, unsigned int frame) {
    if (pagetable->insert(logicalAddr, frame)) {
        return MISS;
    } else {
        return HIT;
    }
}

int getFrame(PAGETABLE *pagetable, unsigned int logicalAddr) {
    return pagetable->getFrameNumber(logicalAddr);
}

int getPhysicalAddr(PAGETABLE *pagetable, unsigned int logicalAddr) {
    int frameNumber = getFrame(pagetable, logicalAddr);
    int pageSize = pagetable->entryCountArray[pagetable->levelCount];
    int startingPhysicalLocation = frameNumber * pageSize;
    int bitMask = pagetable->levelBitmaskArray[pagetable->levelCount];
    int offset = logicalAddr & bitMask;
    return startingPhysicalLocation + offset;
}

//Formats end of run output statistics
void printHelper(int size, int hits, int missess, unsigned int pageSize) {
    double total = hits + missess;
    cout << "Page table size: " << pageSize << endl;
    cout << setprecision(4) << "Hits " << hits << " (" << hits / total * 100;
    cout << "%), Misses " << missess << " (" << missess / total * 100 << "%) ";
    cout << setprecision(100) << "# Addressess " << total << endl;
    cout << "Bytes used: " << size << endl;
}

void tFlagHelper(PAGETABLE *pagetable, unsigned int logicalAddress, bool tFlag) {
    if (tFlag) {
        int physicalAddress = getPhysicalAddr(pagetable, logicalAddress);
        printf("%08X -> %08X\n", logicalAddress, physicalAddress);
    }
}

void pFlagHelper(PAGETABLE *pt, string file, int addressSizeUsed, bool pFlag) {
    if (pFlag) {
        FILE *filePointer;
        if ((filePointer = fopen(file.c_str(), "w")) == nullptr) {
            fprintf(stderr, "Can not open %s for writing\n", file.c_str());
            exit(FILE_OPEN_ERROR);
        }
        // 1 << adressSizeUsed is equivalent to 2^(# bits not in offset)
        int maxPageNumber = 1 << addressSizeUsed;
        //Initialize all bool flags in array to 0
        bool *frameNumberOutputed = new bool[maxPageNumber];
        for (int i = 0; i < maxPageNumber; i++) {
            frameNumberOutputed[i] = false;
        }
        int offset = pt->levelShiftArray[pt->levelCount - 1];
        int frameNumber;
        int pageNumber;
        for (int i = 0; i < maxPageNumber; i++) {
            //Converts a Page Number to a Logical Address w/ offset = 0
            pageNumber = i << offset;
            frameNumber = pt->getFrameNumber(pageNumber);
            //Only print valid frames once
            if (frameNumber != INVALID) {
                if (!frameNumberOutputed[frameNumber]) {
                    fprintf(filePointer, "%08X -> %08X\n", i, frameNumber);
                    frameNumberOutputed[frameNumber] = true;
                }
            }

        }
        delete[] frameNumberOutputed;
        fclose(filePointer);
    }
}
