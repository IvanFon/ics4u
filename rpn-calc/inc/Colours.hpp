/**
 * @file Colours.hpp
 * @brief Colour constants
 * @author Ivan Fonseca
 * @copyright GPL-3.0
 */

#ifndef INC_COLOURS_HPP
#define INC_COLOURS_HPP

#include <allegro5/allegro.h>

/// @brief White
extern ALLEGRO_COLOR COL_WHITE;
/// @brief Black
extern ALLEGRO_COLOR COL_BLACK;
/// @brief Red text colour
extern ALLEGRO_COLOR COL_RED;
/// @brief Background colour
extern ALLEGRO_COLOR COL_BACK;
/// @brief Foreground colour
extern ALLEGRO_COLOR COL_FORE;
/// @brief Medium text colour
extern ALLEGRO_COLOR COL_MED_TEXT;

/// @brief Load colours
void loadColours();

#endif  // INC_COLOURS_HPP
