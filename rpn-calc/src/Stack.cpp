/**
 * @file Stack.cpp
 * @brief Stack class
 * @author Ivan Fonseca
 * @copyright GPL-3.0
 */

#include "Stack.hpp"

#include <algorithm>
#include <iostream>

Stack::Stack(): top(-1) { }

bool Stack::isEmpty() {
    return (top < 0);
}

void Stack::push(double c) {
    if (top < (STACK_SIZE - 1)) {
        top++;
        stack[top] = c;
    } else {
        std::cerr << "Error: stack size ("
            << STACK_SIZE << ") exceeded" << std::endl;
            return;
    }
}

double Stack::pop() {
    double res;
    if (!isEmpty()) {
        res = stack[top];
        top--;
    } else {
        std::cerr << "Error: can't pop item from empty stack" << std::endl;
        res = 0;
    }

    return res;
}

void Stack::clear() {
    top = -1;
}
