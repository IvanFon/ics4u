/**
 * @file Init.hpp
 * @brief Initialize Allegro and load assets
 * @author Ivan Fonseca
 * @copyright GPL-3.0
 */

#ifndef INC_INIT_HPP_
#define INC_INIT_HPP_

#include <string>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

#include "Vector.hpp"

/// @brief Allegro display
extern ALLEGRO_DISPLAY *display;
/// @brief Timer
extern ALLEGRO_TIMER *algoTimer;
/// @brief Font
extern ALLEGRO_FONT *font;

/// @brief Screen dimensions
extern Vector screen;

/// @brief Font file path
const char fontPath[] = "./res/fonts/Roboto_Mono/RobotoMono-Regular.ttf";

/// @brief Initialize Allegro
/// @return True if successful, false otherwise
bool initAllegro();

/// @brief Load assets
/// @return True if successful, false otherwise
bool loadAssets();

/// @brief Destroy Allegro objects
void destroyAllegro();

#endif  // INC_INIT_HPP_
