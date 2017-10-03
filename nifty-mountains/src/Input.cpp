/**
 *  @file Input.cpp
 *  @brief Input
 *  @author Ivan Fonseca
 */

#include "Input.hpp"

#include <iostream>
#include <string>
#include <fstream>

#include <apmatrix.h>

bool readFile(const std::string &filename, apmatrix<int> &matrix) {
    // Open file
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file \"" << filename << "\"" << std::endl;
        return false;
    }

    // Read file into matrix
    for (int y = 0; y < matrix.numrows(); y++) {
        for (int x = 0; x < matrix.numcols(); x++) {
            // Read in value
            int tmp;
            file >> tmp;
            // Add to matrix
            matrix[y][x] = tmp;
        }
    }

    file.close();

    return true;
}
