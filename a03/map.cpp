//
// Created by William Fox on 2019-03-05.
//

#include "map.h"

MAP::MAP(int size) {
    MAP::size = size;
    MAP::frameMapping = new int[size];
    for (int i = 0; i < size; i++) {
        frameMapping[i] = INVALID;
    }
}

MAP::~MAP() {
    delete[] frameMapping;
}

int MAP::getFrameNumber(int pageNumber) {
    return frameMapping[pageNumber];
}

bool MAP::insertPageNumber(int pageNumber, int frameNumber) {
    if (frameMapping[pageNumber] != INVALID) {
        return FAILURE;
    }
    frameMapping[pageNumber] = frameNumber;
    return SUCCESS;
}

unsigned int MAP::invalidatePageNumber(int pageNumber) {
    int currentFrameNumber = frameMapping[pageNumber];
    frameMapping[pageNumber] = INVALID;
    return currentFrameNumber;
}

bool MAP::invalidateFrameNumber(int frameNumber) {
    for (int i = 0; i < size; i++) {
        if (frameMapping[i] == frameNumber) {
            frameMapping[i] = INVALID;
            return SUCCESS;
        }
    }
    return FAILURE;
}

int MAP::sizeTotal() {
    return sizeof(size) + sizeof(frameMapping) + sizeof(int) * size;
}
