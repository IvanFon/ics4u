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
/// @param pos Position of mouse
/// @param mousePressed If the left mouse button is pressed
void drawUI(RPNStack stack, const std::string &curIn,
    const Vector &pos, const bool mousePressed);

/// @brief Draw buttons
/// @param pos Mouse position
/// @param mousePressed If the left mouse button is pressed
void drawButtons(const Vector &pos, const bool mousePressed);

/// @brief Handle button clicks
/// @param stack Stack to operate on
/// @param curIn Current input number
/// @param negative If the number is negative
/// @param pos Mouse position
void clickButton(RPNStack &stack, std::string &curIn,
    bool &negative, const Vector &pos);

/// @brief Show an error message
/// @param message Message to display
void showError(const std::string &message);

#endif  // INC_UI_HPP_

