/**
 *  @file Matrix.hpp
 *  @brief Matrix functuions
 *  @author Ivan Fonseca
 */

#ifndef INC_MATRIX_HPP_
#define INC_MATRIX_HPP_

#include <apmatrix.h>

/// @brief Find minimum number in a matrix
/// @param matrix Matrix to search
/// @return Minimum value of the matrix
int matrixMin(const apmatrix<int> &matrix);

/// @brief Find maximum number in a matrix
/// @param matrix Matrix to search
/// @return Maximum value of the matrix
int matrixMax(const apmatrix<int> &matrix);

#endif  // INC_MATRIX_HPP_
