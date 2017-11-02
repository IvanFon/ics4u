/**
 * @file Button.cpp
 * @brief Button class
 * @author Ivan Fonseca
 * @copyright GPL-3.0
 */

#include "Button.hpp"

#include <string>

#include "Vector.hpp"

Button::Button(const Vector &pos, const Vector &size, const std::string &text):
    pos(pos), size(size), text(text) { }

bool Button::collides(const Vector &point) {
    return ((point.x >= pos.x && point.x <= (pos.x + size.x)) &&
            (point.y >= pos.y && point.y <= (pos.y + size.y)));
}
