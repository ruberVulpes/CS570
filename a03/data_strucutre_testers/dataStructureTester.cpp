//
// Created by William Fox on 2019-03-05.
//

#include "../map.h"
#include "../level.h"
#include "../page_table.h"

#include <iostream>
using namespace std;

void testMap();
void testPageTable();

int main(){
    testPageTable();
    testMap();
}

void testPageTable(){
    int testArr[] = {8, 8, 8};
    PAGETABLE(3, testArr);
}

void testMap(){
    MAP map = MAP(100);
    map.insertPageNumber(50, 100);
    map.insertPageNumber(75, 200);
    cout << map.getFrameNumber(10) << endl;
    cout << map.getFrameNumber(50) << endl;
    cout << map.invalidatePageNumber(50) << endl;
    cout << map.getFrameNumber(50) << endl;
    cout << map.getFrameNumber(75) << endl;
    cout << map.invalidateFrameNumber(200) << endl;
    cout << map.getFrameNumber(75) << endl;
}