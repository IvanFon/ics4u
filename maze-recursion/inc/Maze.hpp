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

/// @brief Maze class
class Maze {
  public:
    /// @brief Maze matrix
    std::vector<std::vector<char>> maze;

    /// @brief
    /// @param filename File to load
    Maze(const std::string &filename);
};

#endif  // INC_MAZE_HPP_
