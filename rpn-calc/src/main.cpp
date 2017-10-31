#include <iostream>

#include "Stack.hpp"

int main() {
    Stack stack;

    stack.push(5);
    stack.push(7);
    stack.push(1.2);

    double t = stack.pop();

    return 0;
}
