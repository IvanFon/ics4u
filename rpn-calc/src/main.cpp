#include <iostream>

#include "RPNStack.hpp"

int main() {
    RPNStack stack;

    stack.push(3);
    stack.push(4);
    stack.push(2);
    stack.mul();
    stack.push(1);
    stack.push(5);
    stack.sub();
    stack.push(2);
    stack.push(3);
    stack.pow();
    stack.pow();
    stack.div();
    stack.add();

    std::cout << stack.display() << std::endl;

    return 0;
}
