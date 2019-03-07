//
// Created by William Fox on 2019-03-05.
//

#include "page_table.h"

PAGETABLE::PAGETABLE(int levelCount, int *bitsPerLevel) {
    PAGETABLE::levelCount = levelCount;
    levelBitmaskArray = new int[PAGETABLE::levelCount];
    levelShiftArray = new int[PAGETABLE::levelCount];
    entryCountArray = new int[PAGETABLE::levelCount];
    int offset = ADDRESS_SIZE;
    for (int i = 0; i < PAGETABLE::levelCount; i++) {
        offset -= bitsPerLevel[i];
    }
    int bitsForLevel;
    int cumulativeBitCount = offset;
    for (int i = PAGETABLE::levelCount - 1; i >= 0; i--) {
        bitsForLevel = bitsPerLevel[i];
        // Equivalent to 2 to the power of bitsForLevel
        levelBitmaskArray[i] = ((1 << bitsForLevel) - 1) << cumulativeBitCount;
        levelShiftArray[i] = cumulativeBitCount;
        entryCountArray[i] = 1 << bitsForLevel;
        cumulativeBitCount += bitsForLevel;
    }
    rootNodePtr = new Level(0, 0 == levelCount, this);

};

PAGETABLE::~PAGETABLE() {
    delete levelBitmaskArray;
    delete levelShiftArray;
    delete entryCountArray;
    delete rootNodePtr;
}