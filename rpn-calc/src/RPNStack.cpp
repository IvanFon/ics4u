/**
 * @file RPNStack.cpp
 * @brief RPN calculator stack class
 * @author Ivan Fonseca
 * @copyright GPL-3.0
 */

#include "RPNStack.hpp"

#include <cmath>
#include <iostream>

RPNStack::RPNStack(): Stack() { }

double RPNStack::display() {
    return stack[top];
}

void RPNStack::add() {
    // Check if there are at least two items
    if (top >= 1) {
        double b = pop(), a = pop();
        push(a + b);
    } else {
        std::cerr << "Error: stack must have at least two items" << std::endl;
    }
}

void RPNStack::sub() {
    // Check if there are at least two items
    if (top >= 1) {
        double b = pop(), a = pop();
        push(a - b);
    } else {
        std::cerr << "Error: stack must have at least two items" << std::endl;
    }
}

void RPNStack::mul() {
    // Check if there are at least two items
    if (top >= 1) {
        double b = pop(), a = pop();
        push(a * b);
    } else {
        std::cerr << "Error: stack must have at least two items" << std::endl;
    }
}

void RPNStack::div() {
    // Check if there are at least two items
    if (top >= 1) {
        double b = pop(), a = pop();
        push(a / b);
    } else {
        std::cerr << "Error: stack must have at least two items" << std::endl;
    }
}

void RPNStack::pow() {
    // Check if there are at least two items
    if (top >= 1) {
        double b = pop(), a = pop();
        push(std::pow(a, b));
    } else {
        std::cerr << "Error: stack must have at least two items" << std::endl;
    }
}
