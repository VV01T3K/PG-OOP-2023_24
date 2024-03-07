#include "ONPcalc.h"

#include <iostream>

void ONPcalc::calculate(Stack<Token>& stack) {
    while (!stack.isEmpty()) {
        Token token = stack.pop();
        if (token.type == Token::Type::NUMBER) {
            tmp_stack.push(token.value);
        } else {
            int a, b, c;
            if (!tmp_stack.isEmpty())
                std::cout << token << ' ' << tmp_stack << std::endl;
            switch (token.value) {
                case ADD:
                    a = tmp_stack.pop();
                    b = tmp_stack.pop();
                    tmp_stack.push(a + b);
                    break;
                case SUBTRACT:
                    a = tmp_stack.pop();
                    b = tmp_stack.pop();
                    tmp_stack.push(b - a);
                    break;
                case MULTIPLY:
                    a = tmp_stack.pop();
                    b = tmp_stack.pop();
                    tmp_stack.push(a * b);
                    break;
                case DIVIDE:
                    a = tmp_stack.pop();
                    b = tmp_stack.pop();
                    if (a == 0) {
                        std::cout << "ERROR" << std::endl;
                        tmp_stack.clear();
                        stack.clear();
                        return;
                    }
                    tmp_stack.push(b / a);
                    break;
                case IF:
                    a = tmp_stack.pop();
                    b = tmp_stack.pop();
                    c = tmp_stack.pop();
                    tmp_stack.push(a > 0 ? a : c);
                    break;
                case NOT:
                    a = tmp_stack.pop();
                    tmp_stack.push(-a);
                    break;
                case MAX:
                    while (tmp_stack.getSize() > 1) {
                        a = tmp_stack.pop();
                        b = tmp_stack.pop();
                        tmp_stack.push(a > b ? a : b);
                    }
                    break;
                case MIN:
                    while (tmp_stack.getSize() > 1) {
                        a = tmp_stack.pop();
                        b = tmp_stack.pop();
                        tmp_stack.push(a < b ? a : b);
                    }
                    break;
                default:
                    throw std::invalid_argument("Invalid operator");
            }
        }
    }
    std::cout << tmp_stack.pop() << std::endl;
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