//
// Created by William Fox on 2019-03-05.
//

#ifndef CS570_LEVEL_H
#define CS570_LEVEL_H

#include <stdexcept>
#include <string>

#include "page_table.h"
#include "map.h"

#define nullptr 0

class PAGETABLE;
class Level{
private:
    int depth;
    bool isLeafLevel;
    PAGETABLE * pageTablePtr;
    Level ** nextLevelPtr;
    MAP * mapPtr;
public:
    Level(int, bool, PAGETABLE*);
    ~Level();
    Level *getSubLevel(int);
    MAP *getMap(int);


};

#endif //CS570_LEVEL_H
