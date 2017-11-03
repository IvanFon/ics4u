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
ALLEGRO_COLOR COL_RED;
ALLEGRO_COLOR COL_BACK;
ALLEGRO_COLOR COL_FORE;
unsigned short COL_FORE_R;
unsigned short COL_FORE_G;
unsigned short COL_FORE_B;
ALLEGRO_COLOR COL_MED_TEXT;

void loadColours() {
    COL_WHITE = al_map_rgb(255, 255, 255);
    COL_BLACK = al_map_rgb(0, 0, 0);
    COL_BACK = al_map_rgb(58, 70, 85);
    COL_FORE_R = 55;
    COL_FORE_G = 67;
    COL_FORE_B = 82;
    COL_FORE = al_map_rgb(COL_FORE_R, COL_FORE_G, COL_FORE_B);
    COL_MED_TEXT = al_map_rgb(109, 116, 121);
    COL_RED = al_map_rgb(198, 82, 81);
}
