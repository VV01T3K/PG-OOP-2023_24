_Pragma("once");
#include <iostream>

#include "Stack.h"
#include "Token.h"

class ONPcalc {
   private:
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
