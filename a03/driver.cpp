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
    int argumentCount = 1;
    int nFlag = -1;
    string inputFileName;
    string outputFileName;
    int tFlag = 0;
    int option = 0;
    while ((option = getopt(argc, argv, "n:f:t")) != -1) {
        switch (option) {
            case 'n' :
                nFlag = atoi(optarg);
                argumentCount += 2;
                break;
            case 'f' :
                outputFileName = string(optarg);
                argumentCount += 2;
                break;
            case 't' :
                tFlag = 1;
                argumentCount++;
                break;
            default:
                break;
        }
    }
    inputFileName = argv[argumentCount++];
    int pageTableSizes[argc - argumentCount];
    for (int i = 0; argumentCount < argc; i++) {
        pageTableSizes[i] = atoi(argv[argumentCount++]);
    }
    return 0;
}