//
// Created by William Fox on 2019-03-05.
//

#ifndef CS570_MAP_H
#define CS570_MAP_H

#define INVALID -1
#define FAILURE false
#define SUCCESS true

class MAP{
private:
    int size;
    int *frameMapping;
public:
    MAP(int);
    ~MAP();
    int getFrameNumber(int pageNumber);
    void insertPageNumber(int pageNumber, int frameNumber);
    int invalidatePageNumber(int pageNumber);
    bool invalidateFrameNumber(int frameNumber);
};

#endif //CS570_MAP_H
