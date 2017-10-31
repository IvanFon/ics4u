/**
 * @file Stack.hpp
 * @brief Stack class
 * @author Ivan Fonseca
 * @copyright GPL-3.0
 */

#ifndef INC_STACK_HPP_
#define INC_STACK_HPP_

/// @brief Maximum stack size
const int STACK_SIZE = 20;

/// @brief Stack class
class Stack {
protected:
    /// @brief Top of stack
    int top;
    /// @brief Array storing stack
    double stack[STACK_SIZE];
public:
    /// @brief Create an empty stack
    Stack();

    /// @brief Check if stack is empty
    /// @return True if empty, false otherwise
    bool isEmpty();

    /// @brief Push an item onto the stack
    /// @param c Item to push onto stack
    void push(double c);

    /// @brief Pop the top item from the stack
    /// @return Popped item from stack
    double pop();
};

#endif  // INC_STACK_HPP_
