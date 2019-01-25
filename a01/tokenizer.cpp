//
// Created by William Fox on 1/24/19.
//
#include <cstdio>
#include <readline/readline.h>
#include <string>
#include <sstream>
#include <list>
#include <vector>
#include <iterator>
#include <iostream>
using namespace std;

void printLinkedList(list <string> tokens);
list <string> readInput();
bool isNewToken(char c);
bool isSpecialCharacter(char c);
bool isEscapeCharacter(char c);
bool isSpace(char c);

int main() {
    list<string> tokens = readInput();
    printLinkedList(tokens);
    return 0;
}

list <string> readInput(){
    string userInput = readline(">");
    list <string> tokens;
    ostringstream os;
    for(int i = 0; i < userInput.length(); i++){
        if(isEscapeCharacter(userInput[i])){
            os << userInput[++i];
        } else if (isSpecialCharacter(userInput[i])){
            if(os.str() != ""){
                tokens.push_back(os.str());
                os.str("");
            }
            os << userInput[i];
            tokens.push_back(os.str());
            os.str("");
        } else if(isSpace(userInput[i])){
            if(os.str() != ""){
                tokens.push_back(os.str());
                os.str("");
            }
        } else {
            os << userInput[i];
        }
    }
    if(os.str() != ""){
        tokens.push_back(os.str());
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
