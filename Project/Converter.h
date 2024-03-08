_Pragma("once");

#include <cstring>
#include <iostream>

#include "DoublyLinkedList_Template.h"
#include "ONPcalc.h"
#include "Queue.h"
#include "Stack.h"
#include "Token.h"

using namespace std;

#define MAX_TOKEN_LENGTH 1000

class Converter {
    Stack<Token>& stack;
    Queue<Token> queue;

   public:
    Converter(Stack<Token>& stack) : stack(stack){};
    ~Converter(){};
    void convertOneFormula();
    void finalize();
};

void Converter::finalize() {
    stack.clear();
    while (!queue.isEmpty()) {
        stack.push(queue.get());
    }
};
void Converter::convertOneFormula() {
    char str[MAX_TOKEN_LENGTH];
    // while (cin >> str) {
    // }
    cin >> str;
    queue.put(Token(str));

    finalize();
};