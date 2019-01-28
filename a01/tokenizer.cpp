//
// Created by William Fox on 1/24/19.
//
#include <cstdio>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string>
#include <sstream>
#include <list>
#include <iterator>
#include <iostream>

using namespace std;

void printLinkedList(list <string> tokens);

list <string> readInput(string userInput);

bool isNewToken(char c);

bool isSpecialCharacter(char c);

bool isEscapeCharacter(char c);

bool isSpace(char c);

bool isQuote(char c);

//adds non empty Token to end of the passed List
void addToken(list <string> &tokens, ostringstream &token);

//clears current ostringstream (ie the token)
void clearToken(ostringstream &token);

//A helper function to set the corresponding flag for a quote
void setQuoteFlags(char c, bool &isSingleQuote, bool &isDoubleQuote);

int main() {
    list <string> tokens;
    char *input;
    while((input = readline(">"))){
        add_history(input);
        tokens = readInput(string(input));
        printLinkedList(tokens);
        free(input);
    }
    return 0;
}

list <string> readInput(string userInput) {
    bool insideDoubleQuotes = false;
    bool insideSingleQuotes = false;
    list <string> tokens;
    ostringstream token;

    for (string::iterator iter = userInput.begin(); iter != userInput.end(); iter++) {
        if (isEscapeCharacter(*iter) && !insideSingleQuotes) {
            //Prevents running out of bounds
            if(iter != --userInput.end()) {
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
            } else {
                token << *(iter);
            }
        } else if (isSpecialCharacter(*iter) && !insideSingleQuotes && !insideDoubleQuotes) {
            addToken(tokens, token);
            clearToken(token);

            token << *iter;

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

void printLinkedList(list <string> tokens) {
    if (tokens.size() == 0){
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

void addToken(list <string> &tokens, ostringstream &token) {
    if (token.str() != "") {
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
