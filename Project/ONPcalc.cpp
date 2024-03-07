#include "ONPcalc.h"

int ONPcalc::calculate(Stack<Token>& stack) {
    while (!stack.isEmpty()) {
        Token token = stack.pop();
        if (token.type == Token::Type::NUMBER) {
            tmp_stack.push(token.data);
        } else {
            int a, b, c;
            switch (token.data) {
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
                // case MAX:
                //     tmp_stack.push(a > b ? a : b);
                //     break;
                // case MIN:
                //     tmp_stack.push(a < b ? a : b);
                //     break;
                default:
                    throw std::invalid_argument("Invalid operator");
            }
        }
    }
    return tmp_stack.pop();
};