/**
 * @file Draw.cpp
 * @brief Drawing functions
 * @author Ivan Fonseca
 * @copyright GPL-3.0
 */

#include "Draw.hpp"

#include <iostream>
#include <iomanip>
#include <vector>
#include <sstream>
#include <string>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "Colours.hpp"
#include "Init.hpp"

void drawVector(const std::vector<int> &vect, const std::string &name,
    const int swaps) {
    al_clear_to_color(COL_BLACK);

    // Loop through array
    for (int i = 0; i < vect.size(); i++) {
        // Draw line
        al_draw_line(i, screen.y, i, screen.y - vect[i],
                COL_RED, 1);
    }

    // Draw sorting info
    std::stringstream time;
    time << std::setprecision(3) <<
        (al_get_timer_count(algoTimer) / 100.0) << " seconds";
    std::stringstream swapsStr;
    swapsStr << swaps << " swaps";

    al_draw_text(font, COL_WHITE, 20, 20, 0, name.c_str());
    al_draw_text(font, COL_WHITE, 20, 50, 0, time.str().c_str());
    al_draw_text(font, COL_WHITE, 20, 80, 0, swapsStr.str().c_str());

    al_flip_display();
}

