//
// Created by William Fox on 1/24/19.
//
#include <cstdio>
#include <readline/readline.h>
#include <string>
#include <list>
#include <iostream>
using namespace std;

struct node {
    string token;
    node *next;
};

void printLinkedList(list ){
    cout << "[";
    while(head){
        cout << "{" << head->token << "}";
        head = head->next;
        if(head){
            cout << ",";
        }
    }

    cout << "]" << endl;
}

int main() {
    string userInput = readline(">");
    node *head = new node;
    node *tail = head;
    head->token = userInput[0];
    for(int i = 1; i < userInput.length(); i++){
//        tail->next = new node;
//        tail->next->token = userInput[i];
//        tail = tail->next;
    }
//    cout << head->next->token << endl;
//    printLinkedList(head->next);
    return 0;
}