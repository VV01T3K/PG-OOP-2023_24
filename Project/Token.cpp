#include "Token.h"

#include <iostream>

#include "ONPcalc.h"

int Token::precedence() const {
    if (type == Type::OPERATOR) {
        return ONPcalc::getPriority(value);
    } else {
        return 0;
    }
}

Token::Token(const char* string) {
    if (isdigit(string[0])) {
        type = Type::NUMBER;
        value = atoi(string);
    } else {
        type = Type::OPERATOR;
        switch (string[0]) {
            case '(':
                value = '(';
                break;
            case ')':
                value = ')';
                break;
            case '+':
                value = ONPcalc::ADD;
                break;
            case '-':
                value = ONPcalc::SUBTRACT;
                break;
            case '*':
                value = ONPcalc::MULTIPLY;
                break;
            case '/':
                value = ONPcalc::DIVIDE;
                break;
            case 'I':
            case '?':
                value = ONPcalc::IF;
                break;
            case 'N':
            case '!':
                value = ONPcalc::NOT;
                break;
            case 'M':
                if (string[1] == 'A')
                    value = ONPcalc::MAX;
                else
                    value = ONPcalc::MIN;
                break;
            case '>':
                value = ONPcalc::MAX;
                break;
            case '<':
                value = ONPcalc::MIN;
                break;
            default:
                value = string[0];
                break;
        }
    }
};

// Przeciążenie operatora << dla klasy Token
std::ostream& operator<<(std::ostream& out, const Token& token) {
    if (token.type == Token::Type::NUMBER) {
        out << token.value;
    } else {
        switch (token.value) {
            case ONPcalc::IF:
                out << "IF";
                break;
            case ONPcalc::NOT:
                out << 'N';
                break;
            case ONPcalc::MAX:
                out << "MAX" << (int)token.arg_count;
                break;
            case ONPcalc::MIN:
                out << "MIN" << (int)token.arg_count;
                break;
            default:
                out << (char)token.value;
                break;
        }
    }
    return out;
}