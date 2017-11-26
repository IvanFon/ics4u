/**
 * @file Init.hpp
 * @brief Initialize Allegro
 * @author Ivan Fonseca
 * @license GPL-3.0
 */

#ifndef INC_INIT_HPP_
#define INC_INIT_HPP_

#include <allegro5/allegro.h>

/// @brief Allegro display
extern ALLEGRO_DISPLAY *display;
/// @brief Allegro event queue
extern ALLEGRO_EVENT_QUEUE *evQueue;
/// @brief Redraw timer
extern ALLEGRO_TIMER *drawTimer;

/// @brief Framerate
const double FPS = 60.0;

/// @brief Initialize Allegro
/// @return True if successful, false otherwise
bool initAllegro();

/// @brief Destroy Allegro objects
void destroyAllegro();

#endif  // INC_INIT_HPP_
