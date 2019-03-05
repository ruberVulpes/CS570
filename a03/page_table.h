//
// Created by William Fox on 2019-03-05.
//

#ifndef CS570_PAGE_TABLE_H
#define CS570_PAGE_TABLE_H

#include "level.h"

class  Level;
class PAGETABLE {
public:
    int levelCount;
    int *levelBitmaskArray;
    int *levelShiftArray;
    int *entryCountArray;

    Level *rootNodePtr;

public:

};

#endif //CS570_PAGE_TABLE_H
