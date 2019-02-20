//
// Created by William Fox on 2019-02-19.
//

#include "command.h"

using namespace std;

void execute_commands(list<list<string> > cleanCommandList) {
    int commandTokenSize;
    for (list<list<string> >::iterator iter = cleanCommandList.begin(); iter != cleanCommandList.end(); iter++) {
        commandTokenSize = iter->size();
        char *argv[commandTokenSize + 1];
        list<string>::iterator commandIter = iter->begin();
        if (*commandIter == "pwd") {
            char buff[FILENAME_MAX];
            if (!getcwd(buff, FILENAME_MAX)) {
                cout << "Unable to obtain current directory" << endl;
            } else {
                cout << buff << endl;
            }
        } else if (*commandIter == "cd") {
            if (commandTokenSize != 2) {
                cout << "Accepts exactly one argument" << endl;
            } else {
                commandIter++;
                const char *directory = commandIter->c_str();
                if (chdir(directory) != 0) {
                    cout << "Directory does not exist or is not accessible" << endl;
                }
            }
        } else {
            for (int i = 0; i < commandTokenSize; i++) {
                char *castHelper = new char[commandIter->length() + 1];
                strcpy(castHelper, commandIter->c_str());
                argv[i] = castHelper;
                commandIter++;
            }
            argv[commandTokenSize] = NULL;
            pid_t childPid = fork();
            int status;
            if (childPid == 0) {
                if (execvp(argv[0], argv)) {
                    cout << "Unable to execute " << argv[0] << endl;
                    exit(1);
                }
            } else if (childPid > 0) {
                if (wait(&status) < 0) {
                    cout << "Process exited with error" << endl;
                } else {
                    cout << "Process exited successfully" << endl;
                }
            } else {
                cout << "Unable to spawn program" << endl;
            }

        }
    }
}