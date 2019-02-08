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

//Returns true if c is '\'
bool isEscapeCharacter(char c);

//Returns true if c is whitespace
bool isSpace(char c);

//Returns true if c is a double or single quote
bool isQuote(char c);

//adds non empty Token to end of the passed List
void addToken(list<string> &tokens, ostringstream &token);

//clears current ostringstream (ie the token)
void clearToken(ostringstream &token);

//A helper function to set the corresponding flags for a quote character
void setQuoteFlags(char c, bool &isSingleQuote, bool &isDoubleQuote);

int main() {
    list<string> tokens;
    char *input;
    while ((input = readline(">"))) {
        add_history(input);
        tokens = readInput(string(input));
        printLinkedList(tokens);
        free(input);
    }
    //Print newline to reset outer shell
    cout << endl;
    return 0;
}

list<string> readInput(string userInput) {
    bool insideDoubleQuotes = false;
    bool insideSingleQuotes = false;
    list<string> tokens;
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
            addToken(tokens, token);
            clearToken(token);
            //Insert special char
            token << *iter;
            //End/Add special char token
            addToken(tokens, token);
            clearToken(token);
        } else if (isSpace(*iter) && !insideSingleQuotes && !insideDoubleQuotes) {
            addToken(tokens, token);
            clearToken(token);
        } else {
            token << *iter;
        }
    }
    //Insert last token
    addToken(tokens, token);
    return tokens;
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

bool isEscapeCharacter(char c) {
    return c == '\\';
}

bool isSpace(char c) {
    return isspace(c) != 0;
}

bool isQuote(char c) {
    return c == '\"' || c == '\'';
}

void addToken(list<string> &tokens, ostringstream &token) {
    //Don't add empty tokens
    if (!token.str().empty()) {
        tokens.push_back(token.str());
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
