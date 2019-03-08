//
// Created by William Fox on 2019-03-06.
//
#include "unistd.h"
#include "byutr.h"

#include <stdlib.h>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;
int main(int argc, char *argv[]){
    int nFlag = -1;
    string fileName = "";
    int tFlag = 0;
    int option = 0;
    while((option = getopt(argc, argv, "nft")) != -1){
        switch (option){
            case 'n' : nFlag = atoi(optarg);
                break;
            case 'f' : fileName = string(optarg);
                break;
            case 't' : tFlag = 1;
                break;
            default:
                cout << "idk" << endl;
        }
    }
    cout << nFlag << " file:" << fileName << " tflag: " << tFlag << " " << endl;
    return 0;

}