/**
 *  @file Draw.hpp
 *  @brief Drawing
 *  @author Ivan Fonseca
 */

#ifndef INC_DRAW_HPP_
#define INC_DRAW_HPP_

#include <random>

#include <apmatrix.h>

/// @brief Initialize Allegro and Allegro addons
/// @return true on success, false otherwise
bool initAllegro();

/// @brief Draw a matrix
/// @param matrix Matrix to draw
/// @param min,max Minimum and maximum values of matrix
void drawMatrix(const apmatrix<int> &matrix, int min, int max);

/// @brief Draws lowest elevation path
/// @param matrix Matrix to draw from
/// @param row Row to start from
/// @param rd Random number generator engine
void drawPath(const apmatrix<int> &matrix, int row, std::random_device &rd);

#endif  // INC_DRAW_HPP_
