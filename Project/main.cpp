#include <iostream>

#include "./Stack/Stack.h"

int main() {
    Stack<int> stack;

    // Push elements onto the stack
    stack.push(1);
    stack.push(2);
    stack.push(3);

    // Print the stack
    stack.print();

    // Pop an element from the stack
    int poppedElement = stack.pop();
    std::cout << "Popped: " << poppedElement << std::endl;

    // Print the stack again
    stack.print();

    return 0;
}