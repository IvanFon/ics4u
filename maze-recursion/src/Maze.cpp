/**
 * @file Maze.cpp
 * @brief Maze class
 * @author Ivan Fonseca
 * @license GPL-3.0
 */

#include "Maze.hpp"

#include <fstream>
#include <iostream>
#include <string>

Maze::Maze(const std::string &filename) {
    // Open file
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening maze file \"" << filename << "\"" << std::endl;
        return;
    }
    // Get maze size
    int rows, cols;
    file >> rows >> cols;
    // Read maze
    for (int y = 0; y < rows; y++) {
        std::vector<char> row;
        for (int x = 0; x < cols; x++) {
            char tmp;
            file >> tmp;
            row.push_back(tmp);
        }
        maze.push_back(row);
    }
}
