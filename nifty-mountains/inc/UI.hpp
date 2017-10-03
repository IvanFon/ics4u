/**
 *  @file UI.hpp
 *  @brief UI
 *  @author Ivan Fonseca
 */

#ifndef INC_UI_HPP_
#define INC_UI_HPP_

#include <string>

#include <allegro5/allegro.h>

/// @brief Get filename
/// @param filename Filename
/// @return true on success, false otherwise
bool getFilename(std::string &filename);

#endif  // INC_UI_HPP_