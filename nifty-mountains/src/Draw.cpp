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

    if (!al_install_mouse()) {
        std::cerr << "Error initializing mouse" << std::endl;
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

void drawMatrix(const apmatrix<int> &matrix, int min, int max, bool colour) {
    // Colour scaling
    double scale = 255.0 / (max - min);

    // Loop through map
    for (int y = 0; y < matrix.numrows(); y++) {
        for (int x = 0; x < matrix.numcols(); x++) {
            // Choose colours
            double red = (matrix[y][x] - min) * scale;
            double green = (matrix[y][x] - min) * scale;
            double blue = (matrix[y][x] - min) * scale;
            if (colour) {
                double percentage = (matrix[y][x] - min) / (double)(max - min);
                if (percentage <= 0.33) {
                    red *= 0.8;
                    green *= 0.7;
                } else if (percentage <= 0.66) {
                    blue *= 0.8;
                    green *= 0.8;
                } else {
                    blue *= 0.7;
                    red *= 0.8;
                }
            }
            al_draw_filled_rectangle(
                x, y, x + 1, y + 1,
                al_map_rgb(red, green, blue));
        }
    }
}

std::pair<int, std::vector<int>> drawPath(const apmatrix<int> &matrix,
    int row, ALGORITHM algo) {
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

        // Previous row
        int lastRow = row;

        if (algo == NORMAL) {
            // Forward difference
            int fwd = std::abs(matrix[row][x] - matrix[row][x + 1]);
            // At top
            if (row == 0) {
                // Downward difference
                int dwn = std::abs(matrix[row][x] - matrix[row + 1][x + 1]);
                if (dwn < fwd) {
                    row++;
                }
            // At bottom
            } else if (row == matrix.numrows() - 1) {
                // Upward difference
                int up = std::abs(matrix[row][x] - matrix[row - 1][x + 1]);
                if (up < fwd) {
                    row--;
                }
            // Somewhere in between
            } else {
                // Differences
                int dwn = std::abs(matrix[row][x] - matrix[row + 1][x + 1]);
                int up = std::abs(matrix[row][x] - matrix[row - 1][x + 1]);

                // All equal
                if (fwd == up && fwd == dwn && up == dwn) {
                    // Go forwards (row remains the same)
                // All different
                } else if (fwd != up && fwd != dwn && up != dwn) {
                    // Go to smallest
                    if (fwd < up && fwd < dwn) {
                        // Go forwards (row remains the same)
                    } else if (up < fwd && up < dwn) {
                        // Go up
                        row--;
                    } else {
                        // Go down
                        row++;
                    }
                // Tie between top and bottom
                } else if (up == dwn && fwd != up && fwd != dwn) {
                    if (fwd < up && fwd < dwn) {
                        // Go forwards (row remains the same)
                    } else {
                        // Pick random direction
                        if (dist(mt) == 0) {
                            // Down
                            row++;
                        } else {
                            // Up
                            row--;
                        }
                    }
                // Tie between anything and forwards
                } else {
                    if (fwd <= up && fwd <= dwn) {
                        // Go forwards
                    } else {
                        // Go to lower change in elevation
                        if (up < dwn) {
                            row++;
                        } else {
                            row--;
                        }
                    }
                }
            }
        }  // normal algorithm

        if (algo == DOWNHILL) {
            // Get forwards elevation
            int fwd = matrix[row][x + 1];

            // At top
            if (row == 0) {
                // Get downwards elevation
                int dwn = matrix[row + 1][x + 1];
                if (dwn < fwd) {
                    // Go down
                    row++;
                }
            // At bottom
            } else if (row == matrix.numrows() - 1) {
                // Get upwards elevation
                int up = matrix[row - 1][x + 1];
                if (up < fwd) {
                    // Go up
                    row--;
                }
            // Somewhere in between
            } else {
                // Get elevations
                int up = matrix[row - 1][x + 1];
                int dwn = matrix[row + 1][x + 1];

                if (fwd <= up && fwd <= dwn) {
                    // Go forwards (row remains the same)
                } else if (up < dwn) {
                    // Go up
                    row--;
                } else if (dwn < up) {
                    // Go down
                    row++;
                // Tie between up and down
                } else {
                    // Pick random direction
                    if (dist(mt) == 0) {
                        // Down
                        row++;
                    } else {
                        // Up
                        row--;
                    }
                }
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

void drawAllPaths(const apmatrix<int> &matrix, ALGORITHM algo,
    ALLEGRO_BITMAP *pathsBitmap, ALLEGRO_BITMAP *bestBitmap) {
    // Set drawing target to paths bitmap
    al_set_target_bitmap(pathsBitmap);

    // Get delta elevation and path of first path
    auto firstPath = drawPath(matrix, 0, algo);
    int min = firstPath.first;
    std::vector<int> shortest = firstPath.second;

    // Loop through remaining paths
    for (int i = 1; i < matrix.numrows(); i++) {
        // Get the pair returned by drawPath()
        auto path = drawPath(matrix, i, algo);
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
