#include <iostream>

#include "ONPcalc.h"
// #include "Reader.h"
#include "Stack.h"
using namespace std;

int main() {
    // Stack<Token> stack;
    // {
    //     // 0  1  MAX2  1  N  +  N
    //     stack.push(Token{Token::Type::OPERATOR, ONPcalc::NOT});
    //     stack.push(Token{Token::Type::OPERATOR, ONPcalc::ADD});
    //     stack.push(Token{Token::Type::OPERATOR, ONPcalc::NOT});
    //     stack.push(Token{Token::Type::NUMBER, 1});
    //     stack.push(Token{Token::Type::OPERATOR, ONPcalc::MAX, 2});
    //     stack.push(Token{Token::Type::NUMBER, 1});
    //     stack.push(Token{Token::Type::NUMBER, 0});
    // }

    // stack.print("  ");

    // ONPcalc calc;
    // calc.calculate(stack);
    // stack.clear();

    char input[500];
    cin >> input;
    cout << "===================" << endl << input << endl;

    return 0;
}