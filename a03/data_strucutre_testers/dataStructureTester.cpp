//
// Created by William Fox on 2019-03-05.
//

#include "../map.h"
#include "../level.h"
#include "../page_table.h"

#include <iostream>
using namespace std;
int main(){
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