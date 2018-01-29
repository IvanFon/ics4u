/**
 * @file Draw.hpp
 * @brief Drawing functions
 * @author Ivan Fonseca
 * @copyright GPL-3.0
 */

#ifndef INC_DRAW_HPP_
#define INC_DRAW_HPP_

#include <vector>
#include <string>

/// @brief Draw a vector
/// @param vect Vector to draw
/// @param name Name of algorithm
/// @param swaps Number of swaps
void drawVector(const std::vector<int> &vect, const std::string &name,
    const int swaps);

#endif  // INC_DRAW_HPP_

