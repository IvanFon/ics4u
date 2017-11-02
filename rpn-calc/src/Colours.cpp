/**
 * @file Colours.cpp
 * @brief Colour constants
 * @author Ivan Fonseca
 * @copyright GPL-3.0
 */

#include "Colours.hpp"

#include <allegro5/allegro.h>

ALLEGRO_COLOR COL_WHITE;
ALLEGRO_COLOR COL_BLACK;
ALLEGRO_COLOR COL_BACK;
ALLEGRO_COLOR COL_FORE;

void loadColours() {
    COL_WHITE = al_map_rgb(255, 255, 255);
    COL_BLACK = al_map_rgb(0, 0, 0);
    COL_BACK = al_map_rgb(58, 70, 85);
    COL_FORE = al_map_rgb(55, 67, 82);
}
