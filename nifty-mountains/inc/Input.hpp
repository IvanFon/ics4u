/**
 *  @file Input.hpp
 *  @brief Input
 *  @author Ivan Fonseca
 */

#ifndef INC_INPUT_HPP_
#define INC_INPUT_HPP_

#include <iostream>
#include <string>

#include <allegro5/allegro.h>

#include <apmatrix.h>

#include "Draw.hpp"

/// @brief Read a file into a matrix
/// @param filename Name of file to read
/// @param matrix Matrix to read file into
/// @return True if successful, false otherwise
bool readFile(const std::string &filename, apmatrix<int> &matrix);

/// @brief Checks if any buttons are pressed
/// @param event Allegro event containing mouse data
/// @param algo Algorithm to use
/// @param width Width of map
/// @param drawMap If map should be drawn
/// @param drawPaths If paths should be drawn
/// @param drawBestPath If best path should be drawn
void checkButtons(const ALLEGRO_EVENT event, ALGORITHM &algo, int width, bool &drawMap, bool &drawPaths, bool &drawBestPath);

#endif // INC_INPUT_HPP_
