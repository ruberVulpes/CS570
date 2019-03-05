//
// Created by William Fox on 2019-03-05.
//

#include "level.h"
using namespace std;

Level::Level(int depth, bool isLeafLevel, PAGETABLE* pageTablePtr) {
    Level::depth = depth;
    Level::isLeafLevel = isLeafLevel;
    Level::pageTablePtr = pageTablePtr;
    Level::mapPtr = nullptr;
    if(isLeafLevel){
        Level::nextLevelPtr = nullptr;
    } else {
        int nextLevelSize = Level::pageTablePtr->entryCountArray[depth];
        Level::nextLevelPtr = new Level*[nextLevelSize];
        for(int i = 0; i < nextLevelSize; i++){
            nextLevelPtr[i] = nullptr;
        }
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

Level *Level::getSubLevel(int subLevel) {
    if(isLeafLevel){
        throw runtime_error("Unable to get Sub-Level from a Leaf Level");
    }
    if(nextLevelPtr[subLevel] == nullptr){
        bool isChildLeaf = pageTablePtr->levelCount == depth + 1;
        nextLevelPtr[subLevel] = new Level(depth+1, isChildLeaf, pageTablePtr);
    }
    return nextLevelPtr[subLevel];
}

MAP *Level::getMap(int) {
    if(!isLeafLevel){
        throw runtime_error("Unable to get Map from a non-Leaf Level");
    }
    if(mapPtr == nullptr){
        int mapSize = Level::pageTablePtr->entryCountArray[depth];
        mapPtr = new MAP(mapSize);
    }
    return mapPtr;
}
