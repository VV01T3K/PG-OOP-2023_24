_Pragma("once");
#include <iostream>

#include "Stack.h"

class Token {
   public:
    enum Type { NUMBER, OPERATOR };
    Type type;
    int value;
    unsigned char arg_count;
    friend std::ostream& operator<<(std::ostream& out, const Token& token);
};

class ONPcalc {
   private:
    Stack<int>* stack;
    Stack<int> tmp_stack;

   public:
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
    void calculate(Stack<Token>& stack);
};
