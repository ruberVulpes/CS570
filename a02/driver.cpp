//
// Created by William Fox, cssc1084 on 2019-02-19.
// For Operating Systems @ SDSU Spring 2019

#include <iostream>
#include <readline/readline.h>
#include <readline/history.h>
#include <string>
#include <list>

#include "tokenizer.h"
#include "command.h"

using namespace std;
//Removes unimplemented special characters and replaces pipes with semicolons
list<string> cleanTokens(list<string> tokenList);

//Splits cleanTokenList into seperate commands (if any)
list<list<string> > splitCommands(list<string> cleanTokenList);

int main() {
    list<string> tokenList;
    list<string> cleanTokenList;
    list<list<string> > cleanCommandList;
    char *input;
    while ((input = readline(">"))) {
        add_history(input);
        tokenList = readInput(string(input));
        cleanTokenList = cleanTokens(tokenList);
        cleanCommandList = splitCommands(cleanTokenList);
        execute_commands(cleanCommandList);
        free(input);
    }
    //Print newline to reset outer shell
    cout << endl;
    return 0;
}

list<string> cleanTokens(list<string> tokenList) {
    list<string> cleanTokenList;
    for (list<string>::iterator iter = tokenList.begin(); iter != tokenList.end(); iter++) {
        if (isSpecialCharacter(*iter)) {
            if (*iter == "|") {
                cout << "Pipe not implemented" << endl;
                //Turn |'s into ; for easier checking when splitting commands
                cleanTokenList.push_back(";");
            } else if (*iter == ";") {
                cleanTokenList.push_back(*iter);
            } else {
                cout << "IO redirection and background not implemented" << endl;
                if ((*iter == "<" || *iter == ">") && iter != --tokenList.end()) {
                    //Skip over IO redirection argument
                    iter++;
                }
            }
        } else {
            cleanTokenList.push_back(*iter);
        }
    }
    return cleanTokenList;
}

list<list<string> > splitCommands(list<string> cleanTokenList) {
    list<list<string> > cleanCommandList;
    list<string> currentCleanCommand;
    for (list<string>::iterator iter = cleanTokenList.begin(); iter != cleanTokenList.end(); iter++) {
        if (*iter == ";") {
            if (!currentCleanCommand.empty()) {
                cleanCommandList.push_back(currentCleanCommand);
                currentCleanCommand.erase(currentCleanCommand.begin(), currentCleanCommand.end());
            }
        } else {
            currentCleanCommand.push_back(*iter);
        }
    }
    if (!currentCleanCommand.empty()) {
        cleanCommandList.push_back(currentCleanCommand);
    }
    return cleanCommandList;
}