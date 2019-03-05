//
// Created by William Fox on 2019-03-05.
//

#include "level.h"

Level::Level(int depth, bool isLeafLevel, PAGETABLE* pageTablePtr) {
    Level::depth = depth;
    Level::isLeafLevel = isLeafLevel;
    Level::pageTablePtr = pageTablePtr;
    if(isLeafLevel){
        int mapSize = Level::pageTablePtr->entryCountArray[depth];
        Level::mapPtr = new MAP(mapSize);
        Level::nextLevelPtr = nullptr;
    } else {
        int nextLevelSize = Level::pageTablePtr->entryCountArray[depth];
        Level::nextLevelPtr = new Level*[nextLevelSize];
        Level::mapPtr = nullptr;
    }
}

Level::~Level() {
    if(isLeafLevel){
        delete  mapPtr;
    } else {
        int nextLevelSize = Level::pageTablePtr->entryCountArray[depth];
        for(int i = 0; i < nextLevelSize; i++){
            delete nextLevelPtr[i];
        }
        delete nextLevelPtr;
    }

}
