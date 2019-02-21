//
// Created by William Fox, cssc1084 on 2019-02-19.
// For Operating Systems @ SDSU Spring 2019

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

//Executes list of commands given, expects commands to have been cleaned
void execute_commands(list<list<string> > cleanCommandList);

#endif //CS570_COMMAND_H
