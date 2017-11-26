/**
 * @file UI.hpp
 * @brief UI
 * @author Ivan Fonseca
 * @license GPL-3.0
 */

#ifndef INC_UI_HPP_
#define INC_UI_HPP_

#include <string>

#include <allegro5/allegro.h>

/// @brief Open a filepicker
/// @param filepath Path to file
/// @return True on success, false otherwise
bool getFile(std::string &filepath);

#endif  // INC_UI_HPP_
