_Pragma("once");

#include <cstring>
#include <iostream>

#include "ONPcalc.h"
#include "Stack.h"
#include "Token.h"

using namespace std;

#define MAX_TOKEN_LENGTH 500

class Converter {
    int n;
    Stack<Token>* stack;
    Stack<Token> tmp_stack;

   public:
    Converter(int n, Stack<Token>& stack) : n(n), stack(&stack) {
        cout << "Converter constructor" << endl;
    };
    ~Converter() { cout << "Converter destructor" << endl; };
    void convertOneFormula();
};

void Converter::convertOneFormula() {
    char token[MAX_TOKEN_LENGTH];
    while (cin >> token) {
        if (strcmp(token, ".") == 0) break;

        if (isdigit(token[0])) {
            stack->push(Token{Token::Type::NUMBER, atoi(token)});
        } else {
            switch (token[0]) {
                case '(':
                    stack->push(Token{Token::Type::OPERATOR, '('});
                    break;
                case ')':
                    stack->push(Token{Token::Type::OPERATOR, ')'});
                    break;
                case 'M':
                    if (token[1] == 'A') {
                        stack->push(Token(Token::Type::OPERATOR, ONPcalc::MAX,
                                          token[3]));
                    } else {
                        stack->push(Token(Token::Type::OPERATOR, ONPcalc::MIN,
                                          token[3]));
                    }
                    break;
                case '+':
                    stack->push(Token{Token::Type::OPERATOR, ONPcalc::ADD});
                    break;
                case '-':
                    stack->push(
                        Token{Token::Type::OPERATOR, ONPcalc::SUBTRACT});
                    break;
                case '*':
                    stack->push(
                        Token{Token::Type::OPERATOR, ONPcalc::MULTIPLY});
                    break;
                case '/':
                    stack->push(Token{Token::Type::OPERATOR, ONPcalc::DIVIDE});
                    break;
                case 'N':
                    stack->push(Token{Token::Type::OPERATOR, ONPcalc::NOT});
                    break;
                case 'I':
                    stack->push(Token{Token::Type::OPERATOR, ONPcalc::IF});
                    break;
            }
        }
    }
}