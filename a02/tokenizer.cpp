//
// Created by William Fox, cssc1084, on 2/7/19.
// For Operating Systems @ SDSU Spring 2019
//

#include "tokenizer.h"

using namespace std;

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
