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

void Converter::convertOneFormula() {
    char str[MAX_TOKEN_LENGTH];
    while (cin >> str) {
        Token token(str);
        if (token.isNumber()) {
            queue.put(token);
        } else if (token.isOperator()) {
            while (!stack.isEmpty() && stack.peek().isOperator() &&
                   stack.peek().precedence() >= token.precedence()) {
                queue.put(stack.pop());
            }
            stack.push(token);
        } else if (token.isLeftParenthesis()) {
            stack.push(token);
        } else if (token.isRightParenthesis()) {
            while (!stack.isEmpty() && !stack.peek().isLeftParenthesis()) {
                queue.put(stack.pop());
            }
            if (stack.isEmpty()) {
                cerr << "Error: Mismatched parentheses" << endl;
                exit(1);
            }
            stack.pop();                  // Remove the opening parenthesis
        } else if (token.isFunction()) {  // Handle function names
            int argCount = 1;
            while (!stack.isEmpty() && stack.peek().isNumber()) {
                argCount++;
                stack.pop();
            }
            token.setArgCount(argCount);
            queue.put(token);
        } else {
            cerr << "Error: Invalid character" << endl;
            exit(1);
        }
    }
}

void Converter::finalize() {
    cout << "Queue: " << queue << endl;
    cout << "Stack: " << stack << endl;
    while (!queue.isEmpty()) {
        stack.push(queue.get());
    }
    queue.clear();
}