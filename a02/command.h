//
// Created by William Fox on 2019-02-19.
//

#ifndef CS570_COMMAND_H
#define CS570_COMMAND_H

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <list>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;
//Executes list of commands given
void execute_commands(list<list<string> > cleanCommandList);

#endif //CS570_COMMAND_H
