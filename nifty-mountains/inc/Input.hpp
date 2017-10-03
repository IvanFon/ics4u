/**
 *  @file Input.hpp
 *  @brief Input
 *  @author Ivan Fonseca
 */

#ifndef INC_INPUT_HPP_
#define INC_INPUT_HPP_

#include <iostream>
#include <string>

#include <apmatrix.h>

/// @brief Read a file into a matrix
/// @param filename Name of file to read
/// @param matrix Matrix to read file into
/// @return True if successful, false otherwise
bool readFile(const std::string &filename, apmatrix<int> &matrix);

#endif // INC_INPUT_HPP_
