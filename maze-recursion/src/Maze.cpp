/**
 * @file Maze.cpp
 * @brief Maze class
 * @author Ivan Fonseca
 * @license GPL-3.0
 */

#include "Init.hpp"
#include "Maze.hpp"
#include "Vector.hpp"

#include <fstream>
#include <iostream>
#include <string>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

Maze::Maze(const std::string &filename) {
    // Open file
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening maze file \"" << filename << "\"" << std::endl;
        return;
    }
    // Get maze size
    file >> rows >> cols;
    // Read maze
    for (int y = 0; y < rows; y++) {
        std::vector<char> row;
        for (int x = 0; x < cols; x++) {
            char tmp;
            file >> tmp;
            row.push_back(tmp);
            
            // Store start coordinates
            if (tmp == 'S') {
                start = *(new Vector(x, y));
            }
        }
        maze.push_back(row);
    }
}

void Maze::draw(ALLEGRO_BITMAP *bitmap) {
    // Draw to bitmap
    al_set_target_bitmap(bitmap);

    // Wall colour
    ALLEGRO_COLOR wallCol = al_map_rgb(100, 100, 100);
    // Start colour
    ALLEGRO_COLOR startCol = al_map_rgb(255, 255, 0);
    // Goal colour
    ALLEGRO_COLOR goalCol = al_map_rgb(0, 153, 0);
    // Solution path colour
    ALLEGRO_COLOR pathCol = al_map_rgb(0, 153, 0);

    // Loop through maze
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            // Current drawing position
            Vector drawPos(x * TILE_SIZE, y * TILE_SIZE);
            switch (maze[y][x]) {
                case '#':
                    al_draw_filled_rectangle(drawPos.x, drawPos.y, drawPos.x + TILE_SIZE, drawPos.y + TILE_SIZE, wallCol);
                    break;
                case 'S':
                    al_draw_filled_rectangle(drawPos.x, drawPos.y, drawPos.x + TILE_SIZE, drawPos.y + TILE_SIZE, startCol);
                    break;
                case 'G':
                    al_draw_filled_rectangle(drawPos.x, drawPos.y, drawPos.x + TILE_SIZE, drawPos.y + TILE_SIZE, goalCol);
                    break;
                case '+':
                    al_draw_filled_circle(drawPos.x + (TILE_SIZE / 2), drawPos.y + (TILE_SIZE / 2), TILE_SIZE / 8, pathCol);
                    break;
            }
        }
    }

    // Set drawing target back to window
    al_set_target_backbuffer(display);
}

bool Maze::findPath(int x, int y) {
    // Base cases
    if ((x < 0 || y < 0) || (x >= cols || y >= rows)) {
        // Outside of maze
        return false;
    }
    if (maze[y][x] == 'G') {
        // Goal
        return true;
    }
    if (maze[y][x] != '.') {
        // Not open
        return false;
    }

    maze[y][x] = '+';

    // Check surrounding positions
    if (findPath(x, y - 1)) {
        return true;
    }
    if (findPath(x + 1, y)) {
        return true;
    }
    if (findPath(x, y + 1)) {
        return true;
    }
    if (findPath(x - 1, y)) {
        return true;
    }

    maze[y][x] = '.';

    return false;
}
