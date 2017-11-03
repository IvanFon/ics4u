/**
 * @file Vector.hpp
 * @brief 2D vector class
 * @author Ivan Fonseca
 * @copyright GPL-3.0
 */

#ifndef INC_VECTOR_HPP_
#define INC_VECTOR_HPP_

/// @brief 2D vector class
class Vector {
public:
    /// @{
    /// @brief Coordinates of vector
    int x, y;
    /// @}

    /// @brief Create vector at (0, 0)
    Vector();

    /// @brief Create vector at given coordinates
    /// @param x,y Coordinates
    Vector(int x, int y);
};

#endif  // INC_VECTOR_HPP_
