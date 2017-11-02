/**
 * @file Button.hpp
 * @brief Button class
 * @author Ivan Fonseca
 * @copyright GPL-3.0
 */

#ifndef INC_BUTTON_HPP
#define INC_BUTTON_HPP

#include <string>

#include "Vector.hpp"

class Button {
public:
    /// @brief Button position
    Vector pos;
    /// @brief Button size
    Vector size;
    /// @brief Button text
    std::string text;

    /// @brief Create a button
    /// @param pos Position
    /// @param size Size
    /// @param text Button text
    Button(const Vector &pos, const Vector &size, const std::string &text);

    /// @brief Check if a point collides with this button
    /// @param Point to check for collision with rectangle
    /// @return True if colliding, false otherwise
    bool collides(const Vector &point);
};

#endif // INC_BUTTON_HPP
