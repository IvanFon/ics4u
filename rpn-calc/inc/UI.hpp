/**
 * @file UI.hpp
 * @brief User interface
 * @author Ivan Fonseca
 * @copyright GPL-3.0
 */

#ifndef INC_UI_HPP_
#define INC_UI_HPP_

#include <string>

#include "RPNStack.hpp"
#include "Vector.hpp"

/// @brief Draw user interface
/// @param stack Stack to draw
/// @param curIn Current input
void drawUI(RPNStack stack, const std::string &curIn);

/// @brief Draw buttons
void drawButtons();

/// @brief Handle button clicks
/// @param stack Stack to operate on
/// @param curIn Current input number
/// @param negative If the number is negative
/// @param pos Mouse position
void clickButton(RPNStack &stack, std::string &curIn,
    bool &negative, const Vector &pos);

#endif  // INC_UI_HPP_

