/**
 * @file RPNStack.cpp
 * @brief RPN calculator stack class
 * @author Ivan Fonseca
 * @copyright GPL-3.0
 */

#include "RPNStack.hpp"

#include <cmath>
#include <iostream>
#include <vector>

RPNStack::RPNStack(): Stack() { }

int RPNStack::getTop() {
    return top;
}

double RPNStack::display() {
    if (top >= 0) {
        return stack[top];
    } else {
        std::cerr << "Error: stack has no items, can't display" << std::endl;
        return 0;
    }
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
