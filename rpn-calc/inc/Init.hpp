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
/// @brief Allegro event queue
extern ALLEGRO_EVENT_QUEUE *evQueue;
/// @brief Allegro draw timer
extern ALLEGRO_TIMER *timer;
/// @brief Mouse click timer
extern ALLEGRO_TIMER *mouseTimer;
/// @{
/// @brief Fonts
extern ALLEGRO_FONT *smallFont;
extern ALLEGRO_FONT *smallHeavyFont;
extern ALLEGRO_FONT *medFont;
extern ALLEGRO_FONT *bigFont;
/// @}
/// @brief Small font height
extern int smallFontHeight;

/// @brief Screen dimensions
extern Vector screen;

/// @brief Framerate
const double FPS = 60.0;

/// @{
/// @brief Font file paths
const char smallFontPath[] = "./res/fonts/Roboto_Mono/RobotoMono-Thin.ttf";
const char smallHeavyFontPath[] = "./res/fonts/Roboto_Mono/RobotoMono-Regular.ttf";
const char medFontPath[] = "./res/fonts/YosemiteSanFrancisco/SystemSanFranciscoDisplayRegular.ttf";  /* NOLINT(whitespace/length) */
const char bigFontPath[] = "./res/fonts/YosemiteSanFrancisco/SystemSanFranciscoDisplayThin.ttf";  /* NOLINT(whitespace/length) */
/// @}

/// @brief Initialize Allegro
/// @return True if successful, false otherwise
bool initAllegro();

/// @brief Load assets
/// @return True if successful, false otherwise
bool loadAssets();

/// @brief Destroy Allegro objects
void destroyAllego();

#endif  // INC_INIT_HPP_
