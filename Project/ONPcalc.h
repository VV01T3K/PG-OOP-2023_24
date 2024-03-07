_Pragma("once");
#include <iostream>

#include "Stack.h"

enum Operator {
    ADD = '+',
    SUBTRACT = '-',
    MULTIPLY = '*',
    DIVIDE = '/',
    IF = '?',
    NOT = '!',
    MAX = '>',
    MIN = '<',

};

class Token {
   public:
    enum Type { NUMBER, OPERATOR };
    Type type;
    int value;
    unsigned char arg_count;

    friend std::ostream& operator<<(std::ostream& out, const Token& token) {
        if (token.type == Type::NUMBER) {
            out << token.value;
        } else {
            switch (token.value) {
                case IF:
                    out << "IF";
                    break;
                case NOT:
                    out << 'N';
                    break;
                case MAX:
                    out << "MAX" << (int)token.arg_count;
                    break;
                case MIN:
                    out << "MIN" << (int)token.arg_count;
                    break;
                default:
                    out << (char)token.value;
                    break;
            }
        }
        return out;
    }
};
class ONPcalc {
   private:
    Stack<int>* stack;
    Stack<int> tmp_stack;

   public:
    void calculate(Stack<Token>& stack);
};
