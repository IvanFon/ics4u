/**
 * @file Maze.hpp
 * @brief Maze class
 * @author Ivan Fonseca
 * @license GPL-3.0
 */

#ifndef INC_MAZE_HPP_
#define INC_MAZE_HPP_

#include <string>
#include <vector>

#include <allegro5/allegro.h>

#include "Vector.hpp"

/// @brief Maze class
class Maze {
  public:
    /// @brief Maze matrix
    std::vector<std::vector<char>> maze;
    /// @{
    /// @brief Maze size
    int rows, cols;
    /// @}
    /// @{
    /// @brief Starting position
    Vector start;
    /// @}

    /// @brief Tile size
    static const short TILE_SIZE = 64;

    /// @brief Load a maze
    /// @param filename File to load
    Maze(const std::string &filename);

    /// @brief Draw maze to bitmap
    /// @param bitmap Bitmap to draw maze to
    void draw(ALLEGRO_BITMAP *bitmap);

    /// @brief Find path through maze
    /// @param x,y Coordinates to check
    /// @param path Solution path
    bool findPath(int x, int y);
};

#endif  // INC_MAZE_HPP_
