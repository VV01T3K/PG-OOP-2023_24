#include <iostream>

#include "ONPcalc.h"
#include "Stack.h"
using namespace std;
int main() {
    Stack<Token> stack;
    {
        stack.push(Token{Token::Type::OPERATOR, '!'});
        stack.push(Token{Token::Type::NUMBER, 21});
    }

    cout << "Stack:" << stack << endl;

    ONPcalc calc;
    cout << calc.calculate(stack) << endl;

    return 0;
}