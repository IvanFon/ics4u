/**
 *  @file Matrix.cpp
 *  @brief Input
 *  @author Ivan Fonseca
 */

#include "Matrix.hpp"

int matrixMin(const apmatrix<int> &matrix) {
    if (matrix.numcols() == 0 || matrix.numrows() == 0) {
        return 0;
    }
    // Loop through matrix
    int min = matrix[0][0];
    for (int y = 0; y < matrix.numrows(); y++) {
        for (int x = 0; x < matrix.numcols(); x++) {
            if (matrix[y][x] < min) {
                min = matrix[y][x];
            }
        }
    }

    return min;
}

int matrixMax(const apmatrix<int> &matrix) {
    if (matrix.numcols() <= 0 || matrix.numrows() <= 0) {
        return 0;
    }
    // Loop through matrix
    int max = matrix[0][0];
    for (int y = 0; y < matrix.numrows(); y++) {
        for (int x = 0; x < matrix.numcols(); x++) {
            if (matrix[y][x] > max) {
                max = matrix[y][x];
            }
        }
    }

    return max;
}
