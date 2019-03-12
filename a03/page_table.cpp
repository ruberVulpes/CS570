//
// Created by William Fox on 2019-03-05.
//

#include "page_table.h"

PAGETABLE::PAGETABLE(unsigned int levelCount, int *bitsPerLevel) {
    PAGETABLE::levelCount = levelCount;
    levelBitmaskArray = new unsigned int[PAGETABLE::levelCount + 1];
    levelShiftArray = new unsigned int[PAGETABLE::levelCount + 1];
    entryCountArray = new unsigned int[PAGETABLE::levelCount + 1];
    rootNodePtr = nullptr;

    unsigned int offset = ADDRESS_SIZE;
    for (int i = 0; i < PAGETABLE::levelCount; i++) {
        offset -= bitsPerLevel[i];
    }
    int bitsForLevel;
    unsigned int cumulativeBitCount = offset;
    unsigned int bitMask;
    levelBitmaskArray[levelCount] = (unsigned int) ((1 << offset) - 1);
    levelShiftArray[levelCount] = 0;
    entryCountArray[levelCount] = (unsigned int) (1 << offset);
    for (int i = PAGETABLE::levelCount - 1; i >= 0; i--) {
        bitsForLevel = bitsPerLevel[i];
        // Equivalent to 2 to the power of bitsForLevel
        bitMask = (unsigned int) (1 << bitsForLevel) - 1;
        levelBitmaskArray[i] = bitMask << cumulativeBitCount;
        levelShiftArray[i] = cumulativeBitCount;
        entryCountArray[i] = (unsigned int) 1 << bitsForLevel;
        cumulativeBitCount += bitsForLevel;
    }
};

PAGETABLE::~PAGETABLE() {
    delete[] levelBitmaskArray;
    delete[] levelShiftArray;
    delete[] entryCountArray;
    delete rootNodePtr;
}

bool PAGETABLE::insert(unsigned int logicalAddress, unsigned int frameNumber) {
    if (rootNodePtr == nullptr) {
        rootNodePtr = new Level(0, 1 == levelCount, this);
    }
    return rootNodePtr->insert(logicalAddress, frameNumber);
}

int PAGETABLE::getFrameNumber(unsigned int logicalAddress) {
    if (rootNodePtr == nullptr) {
        return INVALID;
    }
    return rootNodePtr->getFrameNumber(logicalAddress);
}

int PAGETABLE::sizeTotal() {
    int basicSize = sizeof(levelBitmaskArray) + sizeof(levelShiftArray);
    basicSize += sizeof(entryCountArray);
    basicSize *= levelCount;
    basicSize += sizeof(levelCount) + sizeof(rootNodePtr);
    if (rootNodePtr == nullptr) {
        return basicSize;
    }
    return basicSize + rootNodePtr->sizeTotal();
}
