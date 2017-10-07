/**
 *  @file Input.cpp
 *  @brief Input
 *  @author Ivan Fonseca
 */

#include "Input.hpp"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <apmatrix.h>

#include "UI.hpp"

bool readFile(const std::string &filename, apmatrix<int> &matrix) {
    // Open file
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file \"" << filename << "\"" << std::endl;
        return false;
    }

    // Read file into matrix
    // Number of rows
    int rows = 0;
    // Number of columns
    int cols = 0;
    // Entire row from text file
    std::string curRow;
    // If this is the first row
    bool firstRow = true;
    // Read in rows
    while (std::getline(file, curRow)) {
        // Add another row and resize matrix
        rows++;
        matrix.resize(rows, cols);
        // Get row from file
        std::stringstream row(curRow);
        // Current column in current row
        int curCol = 0;
        // Read in values for individual cells
        int val;
        while (row >> val) {
            // Add columns if this is the first row
            if (firstRow) {
                cols++;
                matrix.resize(rows, cols);
            }
            // Set cell value in matrix
            matrix[rows - 1][curCol] = val;
            // Next column
            curCol++;
        }
        // No longer first row
        firstRow = false;
    }

    file.close();

    return true;
}

void checkButtons(const ALLEGRO_EVENT event, ALGORITHM &algo, int width,
    bool &drawMap, bool &mapColours, bool &drawPaths, bool &drawBestPath) {
    // Get mouse coordinates
    int x = event.mouse.x;
    int y = event.mouse.y;

    // Normal algorithm button
    if (x > width + (settingsWidth / 16) &&
        x < width + (settingsWidth / 2) - (settingsWidth / 16) &&
        y > titleHeight &&
        y < titleHeight + 56) {
        algo = NORMAL;
    }

    // Downhill algorithm button
    if (x > width + (settingsWidth / 2) + (settingsWidth / 16) &&
        x < width + settingsWidth - (settingsWidth / 16) &&
        y > titleHeight &&
        y < titleHeight + 56) {
        algo = DOWNHILL;
    }

    // Toggle map button
    if (x > width + (settingsWidth / 16) &&
        x < width + (settingsWidth / 2) - (settingsWidth / 16) &&
        y > titleHeight + 112 &&
        y < titleHeight + 168) {
        drawMap = !drawMap;
    }

    // Toggle map colours button
    if (x > width + (settingsWidth / 2) + (settingsWidth / 16) &&
        x < width + settingsWidth - (settingsWidth / 16) &&
        y > titleHeight + 112 &&
        y < titleHeight + 168) {
        mapColours = !mapColours;
    }

    // Toggle paths button
    if (x > width + (settingsWidth / 16) &&
        x < width + (settingsWidth / 2) - (settingsWidth / 16) &&
        y > titleHeight + 192 &&
        y < titleHeight + 248) {
        drawPaths = !drawPaths;
    }

    // Toggle best path button
    if (x > width + (settingsWidth / 2) + (settingsWidth / 16) &&
        x < width + settingsWidth - (settingsWidth / 16) &&
        y > titleHeight + 192 &&
        y < titleHeight + 248) {
        drawBestPath = !drawBestPath;
    }
}
