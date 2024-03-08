_Pragma("once");

#include <cstring>
#include <iostream>

#include "DoublyLinkedList_Template.h"
#include "ONPcalc.h"
#include "Stack.h"
#include "Token.h"

using namespace std;

#define MAX_TOKEN_LENGTH 500

class Converter {
    Stack<Token>& stack;
    DoublyLinkedList<Token> output;

   public:
    Converter(Stack<Token>& stack) : stack(stack){};
    ~Converter(){};
    void convertOneFormula();
};

void Converter::convertOneFormula() {
    char token[MAX_TOKEN_LENGTH];
    while (cin >> token) {
        cout << token[0] << ": " << ONPcalc::getPriority(token[0]) << endl;
        if (token[0] == '.') break;
        if (isdigit(token[0])) {
            output.insertAtEnd(Token{Token::Type::NUMBER, atoi(token)});
        } else {
            switch (token[0]) {
                case '(':
                    stack.push(Token{Token::Type::OPERATOR, token[0]});
                    break;
                case ')':
                    while (!stack.isEmpty()) {
                        Token tmp = stack.pop();
                        if (tmp.value == '(')
                            break;
                        else
                            output.insertAtEnd(tmp);
                    }
                    break;
                default:
                    while (!stack.isEmpty() &&
                           ONPcalc::getPriority(token[0]) <=
                               ONPcalc::getPriority(stack.peek().value)) {
                        output.insertAtEnd(stack.pop());
                    }
                    stack.push(Token{Token::Type::OPERATOR, token[0]});
                    break;
            }
        }
    }
    while (!stack.isEmpty()) {
        output.insertAtEnd(stack.pop());
    }
    stack.clear();
    output = stack.swapList(output);
}