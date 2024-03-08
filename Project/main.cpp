#include <iostream>

#include "Converter.h"
#include "ONPcalc.h"
#include "Stack.h"
using namespace std;

int main() {
    Stack<Token> stack;

    int n;
    cin >> n;
    Converter converter(stack);

    converter.convertOneFormula();

    stack.print("  ");

    // ONPcalc calc;
    // calc.calculate(stack);

    return 0;
}