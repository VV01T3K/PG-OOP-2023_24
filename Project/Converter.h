_Pragma("once");

#include <cstring>
#include <iostream>

#include "DoublyLinkedList_Template.h"
#include "ONPcalc.h"
#include "Stack.h"
#include "Token.h"

using namespace std;

#define MAX_TOKEN_LENGTH 1000

class Converter {
    Stack<Token>& stack;
    DoublyLinkedList<Token> output;

   public:
    Converter(Stack<Token>& stack) : stack(stack){};
    ~Converter(){};
    void convertOneFormula();
};

void Converter::convertOneFormula() {
    char str[MAX_TOKEN_LENGTH];
    while (cin >> str) {
        if (str[0] == '.') break;
        if (str[0] == ',') continue;

        const Token token(str);
        if (token.type == Token::Type::NUMBER) {
            output.insertAtEnd(token);
            cout << token << " | ";
            cout << output << " | " << stack << endl;
            cout << "----------------" << endl;
            continue;
        }
        switch (token.value) {
            case '(':
                stack.push(token);
                break;
            case ')':
                while (!stack.isEmpty() && stack.peek().value != '(') {
                    output.insertAtEnd(stack.pop());
                }
                if (!stack.isEmpty() && stack.peek().value == '(') {
                    stack.pop();
                }
                break;
            default:
                const int priority = ONPcalc::getPriority(token.value);
                while (!stack.isEmpty() && stack.peek().value != '(' &&
                       ONPcalc::getPriority(stack.peek().value) >= priority) {
                    output.insertAtEnd(stack.pop());
                }
                stack.push(token);
                break;
        }
        cout << token << " | ";
        cout << output << " | " << stack << endl;
        cout << "----------------" << endl;
    }
    while (!stack.isEmpty()) {
        output.insertAtEnd(stack.pop());
    }
    output = stack.swapList(output);
}