//
// Created by William Fox on 1/24/19.
//
#include <cstdio>
#include <readline/readline.h>
#include <string>
#include <sstream>
#include <list>
#include <iterator>
#include <iostream>
using namespace std;

void printLinkedList(list <string> tokens);
list <string> readInput();
bool isNewToken(char c);
bool isSpecialCharacter(char c);
bool isEscapeCharacter(char c);
bool isSpace(char c);

//adds non empty Token to end of List
void addToken(list<string> &tokens, ostringstream &token);
void clearToken(ostringstream &token);

int main() {
    list<string> tokens = readInput();
    printLinkedList(tokens);
    return 0;
}

list <string> readInput(){
    string userInput = readline(">");
    list <string> tokens;
    ostringstream token;
    for(string :: iterator iter = userInput.begin(); iter != userInput.end(); iter++){
        if(isEscapeCharacter(*iter)){
            token << *(++iter);
        } else if (isSpecialCharacter(*iter)){
            addToken(tokens, token);
            clearToken(token);

            token << *iter;

            addToken(tokens, token);
            clearToken(token);
        } else if(isSpace(*iter)){
            addToken(tokens, token);
            clearToken(token);
        } else {
            token << *iter;
        }
    }
    //Insert last token
    addToken(token);
    }
    return tokens;
}

void printLinkedList(list <string> tokens){
    cout << "[";
    for(list<string> :: iterator it = tokens.begin(); it != tokens.end(); it++){
        cout << "{" << *it << "}";
        // Prevents extra comma separator for last element
        if(it != --tokens.end()){
            cout << ",";
        }
    }
    cout << "]" << endl;
}

bool isSpecialCharacter(char c){
    char specialCharacters[] = {'|', ';', '<', '>', '&'};
    int length = sizeof(specialCharacters)/sizeof(specialCharacters[0]);
    for(int i = 0; i < length; i ++){
        if(c == specialCharacters[i]){
            return true;
        }
    }
    return false;
}

bool isEscapeCharacter(char c){
    return c == '\\';
}

bool isSpace(char c){
    return isspace(c) != 0;
}

void addToken(list<string> &tokens, ostringstream &token){
    if(token.str() != ""){
        tokens.push_back(token.str());
    }
}
void clearToken(ostringstream &token){
    token.str("");
}