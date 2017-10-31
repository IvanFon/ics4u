/**
 * @file RPNStack.hpp
 * @brief RPN calculator stack class
 * @author Ivan Fonseca
 * @copyright GPL-3.0
 */

#ifndef INC_RPNSTACK_HPP_
#define INC_RPNSTACK_HPP_

#include "Stack.hpp"

/// @brief RPN calculator stack class
class RPNStack : public Stack {
public:
    /// @brief Create empty RPN calculator stack
    RPNStack();

    /// @brief Get top value from stack without popping it
    double display();

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
};

#endif  // INC_RPNSTACK_HPP_
