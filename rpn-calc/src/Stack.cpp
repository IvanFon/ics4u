/**
 * @file Stack.cpp
 * @brief Stack class
 * @author Ivan Fonseca
 * @copyright GPL-3.0
 */

#include "Stack.hpp"

#include <algorithm>
#include <iostream>

Stack::Stack(): top(-1) {
    std::fill(stack, stack + STACK_SIZE, 0);
}

int Stack::getTop() {
    return top;
}

bool Stack::isEmpty() {
    return (top < 0);
}

void Stack::push(double c) {
    if (top < (STACK_SIZE - 1)) {
        stack[++top] = c;
    } else {
        std::cerr << "Error: stack size ("
            << STACK_SIZE << ") exceeded" << std::endl;
            return;
    }
}

double Stack::pop() {
    if (!isEmpty()) {
        return stack[top--];
    } else {
        std::cerr << "Error: can't pop item from empty stack" << std::endl;
        return 0.0;
    }
}
