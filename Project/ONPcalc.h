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
    static unsigned short getPriority(char op) {
        switch (op) {
            case ONPcalc::ADD:
            case ONPcalc::SUBTRACT:
                return 5;
            case ONPcalc::MULTIPLY:
            case ONPcalc::DIVIDE:
                return 4;
            case ONPcalc::IF:
                return 3;
            case ONPcalc::NOT:
                return 2;
            case ONPcalc::MAX:
            case ONPcalc::MIN:
                return 1;
            default:
                return 0;
        }
    }
    void calculate(Stack<Token>& stack);
};
