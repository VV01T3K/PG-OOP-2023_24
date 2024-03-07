_Pragma("once");
#include <iostream>

#include "Stack.h"

#define NUMBER_OF_IMPLEMENTED_OPERATORS 9

class Token {
   public:
    enum Type { NUMBER, OPERATOR };
    Type type;
    int data;

    friend std::ostream& operator<<(std::ostream& out, const Token& token) {
        if (token.type == Type::NUMBER) {
            out << token.data;
        } else {
            out << (char)token.data;
        }
        return out;
    }
};

class ONPcalc {
   private:
    Stack<int>* stack;
    Stack<int> tmp_stack;

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
    const char operators[NUMBER_OF_IMPLEMENTED_OPERATORS] = "+-*/!?><";

   public:
    int calculate(Stack<Token>& stack);
};
