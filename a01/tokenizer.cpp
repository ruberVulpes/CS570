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
        os << userInput[i];
        tokens.push_back(os.str());
        os.str("");
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
