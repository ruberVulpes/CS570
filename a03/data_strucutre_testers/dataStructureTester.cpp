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
//    testPageTable();
    testMap();
}

void testPageTable(){
    int testArr[] = {8, 8, 8};
    PAGETABLE pagetable = PAGETABLE(3, testArr);
    cout << pagetable.insert(0xFE0123C2, 4) << endl;
    cout << sizeof(pagetable.rootNodePtr) << endl;
    cout << pagetable.insert(0xFF0124C4, 222) << endl;
    cout << sizeof(pagetable.rootNodePtr) << endl;
    cout << pagetable.insert(0x010124C4, 222) << endl;
    cout << sizeof(pagetable) << endl;
    cout << pagetable.getFrameNumber(0xFF0124C4) << endl;
    cout << pagetable.getFrameNumber(0xFE0120C4) << endl;
}

void testMap(){
    MAP map(100);
    cout << sizeof(map) << endl;
    cout << map.sizeTotal() << endl;
    cout << sizeof(MAP(100)) << endl;
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