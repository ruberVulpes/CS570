//
// Created by William Fox, cssc1084, on 1/24/19.
// For Operating Systems @ SDSU Spring 2019
//
#include <cstdio>
#include <cstdlib>
#include <readline/readline.h>
#include <readline/history.h>
#include <string>
#include <sstream>
#include <list>
#include <iterator>
#include <iostream>

using namespace std;

void printLinkedList(list<string> tokens);

//Returns a linked list of tokenized strings
list<string> readInput(string userInput);

//Returns true if c is one of |, ;, <, >, &
bool isSpecialCharacter(char c);

bool isSpecialCharacter(string c);

//Returns true if c is '\'
bool isEscapeCharacter(char c);

//Returns true if c is whitespace
bool isSpace(char c);

//Returns true if c is a double or single quote
bool isQuote(char c);

//adds non empty Token to end of the passed List
void addToken(list<string> &tokenList, ostringstream &token);

//clears current ostringstream (ie the token)
void clearToken(ostringstream &token);

//A helper function to set the corresponding flags for a quote character
void setQuoteFlags(char c, bool &isSingleQuote, bool &isDoubleQuote);

list<string> cleanTokens(list<string> tokenList);

list<list<string> > splitCommands(list<string> cleanTokenList);

int main() {
    list<string> tokenList;
    list<string> cleanTokenList;
    list<list<string> > cleanCommandList;
    char *input;
    while ((input = readline(">"))) {
        add_history(input);
        tokenList = readInput(string(input));
        cout << "Dirty" << endl;
        printLinkedList(tokenList);
        cout << "Clean"<< endl;
        cleanTokenList = cleanTokens(tokenList);
        printLinkedList(cleanTokenList);
        cout << "Seperated" << endl;
        cleanCommandList = splitCommands(cleanTokenList);
        for(list<list<string> >::iterator iter = cleanCommandList.begin(); iter != cleanCommandList.end(); iter++){
            printLinkedList(*iter);
        }
        cout << "end" << endl;
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

list<list<string> > splitCommands(list<string> cleanTokenList){
    list<list<string> > cleanCommandList;
    list<string> currentCleanCommand;
    for(list<string>::iterator iter = cleanTokenList.begin(); iter != cleanTokenList.end(); iter++){
        if(*iter == ";"){
            if(!currentCleanCommand.empty()){
                cleanCommandList.push_back(currentCleanCommand);
                currentCleanCommand.clear();
            }
        } else {
            currentCleanCommand.push_back(*iter);
        }
    }
    if(!currentCleanCommand.empty()) {
        cleanCommandList.push_back(currentCleanCommand);
    }
        return cleanCommandList;
}

list<string> readInput(string userInput) {
    bool insideDoubleQuotes = false;
    bool insideSingleQuotes = false;
    list<string> tokenList;
    ostringstream token;

    for (string::iterator iter = userInput.begin(); iter != userInput.end(); iter++) {
        if (isEscapeCharacter(*iter) && !insideSingleQuotes) {
            //Prevents running out of bounds
            if (iter != --userInput.end()) {
                //Add next character regardless
                token << *(++iter);
            }
        } else if (isQuote(*iter)) {
            //Start of a new quote section
            if (!insideSingleQuotes && !insideDoubleQuotes) {
                setQuoteFlags(*iter, insideSingleQuotes, insideDoubleQuotes);
                //Ending a double quote section
            } else if (*iter == '\"' && insideDoubleQuotes) {
                insideDoubleQuotes = false;
                //Ending a single quote section
            } else if (*iter == '\'' && insideSingleQuotes) {
                insideSingleQuotes = false;
                //Inside quotes, add quote char as literal
            } else {
                token << *iter;
            }
        } else if (isSpecialCharacter(*iter) && !insideSingleQuotes && !insideDoubleQuotes) {
            //End/Add old token
            addToken(tokenList, token);
            clearToken(token);
            //Insert special char
            token << *iter;
            //End/Add special char token
            addToken(tokenList, token);
            clearToken(token);
        } else if (isSpace(*iter) && !insideSingleQuotes && !insideDoubleQuotes) {
            addToken(tokenList, token);
            clearToken(token);
        } else {
            token << *iter;
        }
    }
    //Insert last token
    addToken(tokenList, token);
    return tokenList;
}

void printLinkedList(list<string> tokens) {
    if (tokens.empty()) {
        return;
    }
    cout << "[";
    for (list<string>::iterator it = tokens.begin(); it != tokens.end(); it++) {
        cout << "{" << *it << "}";
        // Prevents extra comma separator for last element
        if (it != --tokens.end()) {
            cout << ",";
        }
    }
    cout << "]" << endl;
}

bool isSpecialCharacter(char c) {
    char specialCharacters[] = {'|', ';', '<', '>', '&'};
    int length = sizeof(specialCharacters) / sizeof(specialCharacters[0]);
    for (int i = 0; i < length; i++) {
        if (c == specialCharacters[i]) {
            return true;
        }
    }
    return false;
}

bool isSpecialCharacter(string c) {
    return isSpecialCharacter(c.at(0));
}

bool isEscapeCharacter(char c) {
    return c == '\\';
}

bool isSpace(char c) {
    return isspace(c) != 0;
}

bool isQuote(char c) {
    return c == '\"' || c == '\'';
}

void addToken(list<string> &tokenList, ostringstream &token) {
    //Don't add empty tokens
    if (!token.str().empty()) {
        tokenList.push_back(token.str());
    }
}

void clearToken(ostringstream &token) {
    token.str("");
}

void setQuoteFlags(char c, bool &isSingleQuote, bool &isDoubleQuote) {
    if (c == '\"') {
        isDoubleQuote = true;
    } else if (c == '\'') {
        isSingleQuote = true;
    } else {
        //Do Nothing
    }
}
