//
// Created by William Fox on 2019-03-05.
//

#ifndef CS570_PAGE_TABLE_H
#define CS570_PAGE_TABLE_H

#include "level.h"
#define ADDRESS_SIZE 32

class  Level;
class PAGETABLE {
public:
    int levelCount;
    int *levelBitmaskArray;
    int *levelShiftArray;
    int *entryCountArray;

    PAGETABLE(int, int*);
    ~PAGETABLE();

private:
    Level *rootNodePtr;
    int currentFrame = 0;
};

#endif //CS570_PAGE_TABLE_H
