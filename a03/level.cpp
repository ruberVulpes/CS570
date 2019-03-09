//
// Created by William Fox on 2019-03-05.
//

#include "level.h"

using namespace std;

Level::Level(int depth, bool isLeafLevel, PAGETABLE *pageTablePtr) {
    Level::depth = depth;
    Level::isLeafLevel = isLeafLevel;
    Level::pageTablePtr = pageTablePtr;
    Level::mapPtr = nullptr;
    if (isLeafLevel) {
        Level::nextLevelPtr = nullptr;
    } else {
        int nextLevelSize = Level::pageTablePtr->entryCountArray[depth];
        Level::nextLevelPtr = new Level *[nextLevelSize];
        for (int i = 0; i < nextLevelSize; i++) {
            nextLevelPtr[i] = nullptr;
        }
    }
}

Level::~Level() {
    if (isLeafLevel) {
        delete mapPtr;
    } else {
        int nextLevelSize = Level::pageTablePtr->entryCountArray[depth];
        for (int i = 0; i < nextLevelSize; i++) {
            delete nextLevelPtr[i];
        }
        delete nextLevelPtr;
    }

}

Level *Level::getSubLevel(int subLevel) {
    if (isLeafLevel) {
        throw runtime_error("Unable to get Sub-Level from a Leaf Level");
    }
    if (nextLevelPtr[subLevel] == nullptr) {
        bool isChildLeaf = pageTablePtr->levelCount == depth + 1;
        nextLevelPtr[subLevel] = new Level(depth + 1, isChildLeaf, pageTablePtr);
    }
    return nextLevelPtr[subLevel];
}

MAP *Level::getMap(int) {
    if (!isLeafLevel) {
        throw runtime_error("Unable to get Map from a non-Leaf Level");
    }
    if (mapPtr == nullptr) {
        int mapSize = Level::pageTablePtr->entryCountArray[depth];
        mapPtr = new MAP(mapSize);
    }
    return mapPtr;
}

bool Level::insert(unsigned int logicalAddress, unsigned int frameNumber) {
    unsigned int bitmask = pageTablePtr->levelBitmaskArray[depth];
    unsigned int shift = pageTablePtr->levelShiftArray[depth];
    unsigned int location = (logicalAddress & bitmask) >> shift;

    if (isLeafLevel) {
        if (mapPtr == nullptr) {
            mapPtr = new MAP(pageTablePtr->entryCountArray[depth]);
        }
        return mapPtr->insertPageNumber(location, frameNumber);
    }
    if (nextLevelPtr[location] == nullptr) {
        bool isChildLeaf = pageTablePtr->levelCount == depth + 2;
        nextLevelPtr[location] = new Level(depth + 1, isChildLeaf, pageTablePtr);
    }
    return nextLevelPtr[location]->insert(logicalAddress, frameNumber);

}

int Level::getFrameNumber(unsigned int logicalAddress) {
    unsigned int bitmask = pageTablePtr->levelBitmaskArray[depth];
    unsigned int shift = pageTablePtr->levelShiftArray[depth];
    unsigned int location = (logicalAddress & bitmask) >> shift;
    if (isLeafLevel) {
        if (mapPtr == nullptr) {
            return INVALID;
        } else {
            return mapPtr->getFrameNumber(location);
        }
    } else {
        if(nextLevelPtr[location] == nullptr){
            return INVALID;
        } else {
            return nextLevelPtr[location]->getFrameNumber(logicalAddress);
        }
    }
}

int Level::sizeTotal() {
    int basicSize = sizeof(depth) + sizeof(isLeafLevel) + sizeof(pageTablePtr);
    basicSize += sizeof(nextLevelPtr) + sizeof(mapPtr);
    int subSize = 0;
    if(isLeafLevel){
        if(mapPtr == NULL){
            return basicSize;
        }
        return basicSize + mapPtr->sizeTotal();
    }
    for (int i = 0; i < pageTablePtr->entryCountArray[depth]; i++) {
        if(nextLevelPtr[i] != NULL){
            subSize += nextLevelPtr[i]->sizeTotal();
        }
    }
    return basicSize + subSize;
}
