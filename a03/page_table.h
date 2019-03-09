//
// Created by William Fox on 2019-03-05.
//

#ifndef CS570_PAGE_TABLE_H
#define CS570_PAGE_TABLE_H

#include "level.h"
#define ADDRESS_SIZE 32
#define SELF_DEPTH 0
#define nullptr 0

class  Level;
class PAGETABLE {
public:
    unsigned int levelCount;
    unsigned int *levelBitmaskArray;
    unsigned int *levelShiftArray;
    unsigned int *entryCountArray;

    PAGETABLE(unsigned int, int*);
    ~PAGETABLE();
    bool insert(unsigned int, unsigned int);
    int getFrameNumber(unsigned int);
    int sizeTotal();

//private:
    Level *rootNodePtr;
};

#endif //CS570_PAGE_TABLE_H
