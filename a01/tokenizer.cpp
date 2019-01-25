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

int main() {
    string userInput = readline(">");
    list <string> tokens;
    ostringstream os;
    for(int i = 0; i < userInput.length(); i++){
        os << userInput[i];
        tokens.push_back(os.str());
        os.str("");

    }
    printLinkedList(tokens);
    return 0;
}
