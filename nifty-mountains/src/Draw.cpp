/**
 *  @file Draw.cpp
 *  @brief Drawing
 *  @author Ivan Fonseca
 */

#include "Draw.hpp"

#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <utility>
#include <random>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include <apmatrix.h>

bool initAllegro() {
    if (!al_init()) {
        std::cerr << "Error initializing Allegro" << std::endl;
        return false;
    }

    if (!al_init_primitives_addon()) {
        std::cerr << "Error initializing primitives addon" << std::endl;
        return false;
    }

    if (!al_init_native_dialog_addon()) {
        std::cerr << "Error initializing native dialog addon" << std::endl;
        return false;
    }

    if (!al_init_font_addon()) {
        std::cerr << "Error initializing font addon" << std::endl;
        return false;
    }

    if (!al_init_ttf_addon()) {
        std::cerr << "Error initializing TrueType addon" << std::endl;
        return false;
    }

    return true;
}

void drawMatrix(const apmatrix<int> &matrix, int min, int max) {
    // Colour scaling
    double scale = 255.0 / (max - min);

    // Loop througb map
    for (int y = 0; y < matrix.numrows(); y++) {
        for (int x = 0; x < matrix.numcols(); x++) {
            double colour = (matrix[y][x] - min) * scale;
            al_draw_filled_rectangle(
                x, y, x + 1, y + 1,
                al_map_rgb(colour, colour, colour));
        }
    }
}

std::pair<int, std::vector<int>> drawPath(const apmatrix<int> &matrix, int row) {  /* NOLINT(whitespace/line_length) */
    // Colour to use to draw line
    ALLEGRO_COLOR colour = al_map_rgb(255, 0, 0);
    // Total change in elevation
    int deltaElev = 0;
    // Path taken
    std::vector<int> path;
    // Random number generator
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, 1);

    // Loop until right side of matrix
    for (int x = 0; x < matrix.numcols() - 1; x++) {
        // Choose next row

        // Forward difference
        int fwd = std::abs(matrix[row][x + 1] - matrix[row][x]);
        // Row last step
        int lastRow = row;

        // At top
        if (row == 0) {
           // Downward difference
           int dwn = std::abs(matrix[row + 1][x + 1] - matrix[row][x]);
           // Go down if less change, forwards otherwise (row stays the same)
           if (dwn < fwd) {
               row++;
           }
        // At bottom
        } else if (row == matrix.numrows() - 1) {
            // Upward difference
            int up = std::abs(matrix[row - 1][x + 1] - matrix[row][x]);
            // Go up if less change, forwards otherwise (row stays the same)
            if (up < fwd) {
                row--;
            }
        // Somewhere in between
        } else {
            // Differences
            int dwn = std::abs(matrix[row + 1][x + 1] - matrix[row][x]);
            int up = std::abs(matrix[row - 1][x + 1] - matrix[row][x]);
            // Any tie with forwards
            if (dwn == fwd || up == fwd) {
                // Go forwards (row stays the same)
            // Up and down tie
            } else if (dwn == up) {
                switch (dist(mt)) {
                    case 0:
                        // Go up
                        row--;
                        break;
                    case 1:
                        // Go down
                        row++;
                        break;
                    default:
                        // This should never happen
                        std::cerr << "Error picking random direction"
                            << std::endl;
                        break;
                }
            // No ties, just get smallest
            } else {
                if (up < fwd && up < dwn) {
                    row--;
                } else if (dwn < fwd) {
                    row++;
                }
                // Otherwise go forwards (row stays the same)
            }
        }

        // Draw line
        al_draw_filled_rectangle(
            x, row, x + 1, row + 1,
            colour);
        path.push_back(row);
        deltaElev += std::abs(matrix[lastRow][x] - matrix[row][x + 1]);
    }

    return std::make_pair(deltaElev, path);
}

void drawAllPaths(const apmatrix<int> &matrix, ALLEGRO_BITMAP *pathsBitmap, ALLEGRO_BITMAP *bestBitmap) {  /* NOLINT(whitespace/line_length) */
    // Set drawing target to paths bitmap
    al_set_target_bitmap(pathsBitmap);

    // Get delta elevation and path of first path
    auto firstPath = drawPath(matrix, 0);
    int min = firstPath.first;
    std::vector<int> shortest = firstPath.second;

    // Loop through remaining paths
    for (int i = 1; i < matrix.numrows(); i++) {
        // Get the pair returned by drawPath()
        auto path = drawPath(matrix, i);
        int curMin = path.first;
        std::vector<int> curPath = path.second;
        // Check if current elevation is lower than minimum
        if (curMin < min) {
            min = curMin;
            shortest = curPath;
        }
    }

    // Draw shortest path
    // Set drawing target to best path bitmap
    al_set_target_bitmap(bestBitmap);
    // Colour for best path
    ALLEGRO_COLOR colour = al_map_rgb(0, 255, 0);
    // Draw
    for (int i = 0; i < shortest.size(); i++) {
        al_draw_filled_rectangle(
            i, shortest[i], i + 1, shortest[i] + 1,
            colour);
    }
}
