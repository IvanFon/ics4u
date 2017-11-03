/**
 * @file RPNStack.cpp
 * @brief RPN calculator stack class
 * @author Ivan Fonseca
 * @copyright GPL-3.0
 */

#include "RPNStack.hpp"

#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
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

std::string RPNStack::displayAll() {
    if (top >= 0) {
        std::stringstream out;
        for (int i = 0; i <= top; i++) {
            out << stack[i];
            if (i != top) {
                out << ", ";
            }
        }
        return out.str();
    } else {
        std::cerr << "Error: stack has no items, can't display" << std::endl;
        return "";
    }
}

bool RPNStack::add() {
    // Check if there are at least two items
    if (top >= 1) {
        double b = pop(), a = pop();
        push(a + b);
        return true;
    }

    return false;
}

bool RPNStack::sub() {
    // Check if there are at least two items
    if (top >= 1) {
        double b = pop(), a = pop();
        push(a - b);
        return true;
    }

    return false;
}

bool RPNStack::mul() {
    // Check if there are at least two items
    if (top >= 1) {
        double b = pop(), a = pop();
        push(a * b);
        return true;
    }

    return false;
}

bool RPNStack::div() {
    // Check if there are at least two items
    if (top >= 1) {
        double b = pop(), a = pop();
        push(a / b);
        return true;
    }

    return false;
}

bool RPNStack::pow() {
    // Check if there are at least two items
    if (top >= 1) {
        double b = pop(), a = pop();
        push(std::pow(a, b));
        return true;
    }

    return false;
}

bool RPNStack::root() {
    // Check if there are at least two items
    if (top >= 0) {
        double a = pop();
        push(std::sqrt(a));
        return true;
    }

    return false;
}

bool RPNStack::swap() {
    // Check if there are at least two items
    if (top >= 1) {
        double b = pop(), a = pop();
        push(b);
        push(a);
        return true;
    }

    return false;
}
