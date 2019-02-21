//
// Created by William Fox, cssc1084 on 2019-02-19.
// For Operating Systems @ SDSU Spring 2019

#ifndef CS570_TOKENIZER_H
#define CS570_TOKENIZER_H

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

//Returns true if
//c is one of |, ;, <, >, &
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

#endif //CS570_TOKENIZER_H
