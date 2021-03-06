/**
 *  @file Draw.hpp
 *  @brief Drawing
 *  @author Ivan Fonseca
 */

#ifndef INC_DRAW_HPP_
#define INC_DRAW_HPP_

#include <utility>
#include <vector>
#include <random>

#include <allegro5/allegro.h>

#include <apmatrix.h>

enum ALGORITHM {
    NORMAL,
    DOWNHILL
};

/// @brief Initialize Allegro and Allegro addons
/// @return true on success, false otherwise
bool initAllegro();

/// @brief Draw a matrix
/// @param matrix Matrix to draw
/// @param min,max Minimum and maximum values of matrix
/// @param colour If we should colour the map
void drawMatrix(const apmatrix<int> &matrix, int min, int max, bool colour);

/// @brief Draws lowest elevation path
/// @param matrix Matrix to draw from
/// @param row Row to start from
/// @param algo Algorithm to use
/// @return Total elevation change and path taken
// Tuple lets you return two objects from a function
std::pair<int, std::vector<int>> drawPath(const apmatrix<int> &matrix, int row, ALGORITHM algo);

/// @brief Draw all lowest elevation paths
/// @param matrix Matrix to draw from
/// @param algo Algorithm to use
/// @param pathsBitmap Bitmap to draw paths to
/// @param bestBitmap Bitmap to draw best path to
void drawAllPaths(const apmatrix<int> &matrix, ALGORITHM algo, ALLEGRO_BITMAP *pathsBitmap, ALLEGRO_BITMAP *bestBitmap);

#endif  // INC_DRAW_HPP_
