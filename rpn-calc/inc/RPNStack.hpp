/**
 * @file RPNStack.hpp
 * @brief RPN calculator stack class
 * @author Ivan Fonseca
 * @copyright GPL-3.0
 */

#ifndef INC_RPNSTACK_HPP_
#define INC_RPNSTACK_HPP_

#include <string>
#include <vector>

#include "Stack.hpp"

/// @brief RPN calculator stack class
class RPNStack : public Stack {
public:
    /// @brief Create empty RPN calculator stack
    RPNStack();

    /// @brief Get top index of stack
    /// @return Index of top of stack
    int getTop();

    /// @brief Get top value from stack without popping it
    /// @return Top item of stack
    double display();

    /// @brief Get all items from stack as a string
    /// @return Stack as a string of comma separated values
    std::string displayAll();

    /// @brief Pop top two items off stack and push the sum
    void add();

    /// @brief Pop top two items off stack and push the difference
    void sub();

    /// @brief Pop top two items off stack and push the product
    void mul();

    /// @brief Pop top two items off stack and push the quotient
    void div();

    /// @brief Pop top two items off stack and push the product
    void pow();

    /// @brief Pop top two items off stack and push the root
    void root();
};

#endif  // INC_RPNSTACK_HPP_
