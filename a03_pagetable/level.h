//
// Created by William Fox on 2019-03-05.
//

#ifndef CS570_LEVEL_H
#define CS570_LEVEL_H

#include <stdexcept>
#include <string>

#include "page_table.h"
#include "map.h"

class PAGETABLE;

class Level {
private:
    int depth;
    bool isLeafLevel;
    PAGETABLE *pageTablePtr;
    Level **nextLevelPtr;
    MAP *mapPtr;
public:
    Level(int, bool, PAGETABLE *);

    ~Level();

    Level *getSubLevel(int);

    MAP *getMap(int);

    bool insert(unsigned int, unsigned int);

    int getFrameNumber(unsigned int);

    int sizeTotal();

};

#endif //CS570_LEVEL_H
