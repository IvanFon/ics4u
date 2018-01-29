/**
 * @file Init.cpp
 * @brief Initialize Allegro and load assets
 * @author Ivan Fonseca
 * @copyright GPL-3.0
 */

#include "Init.hpp"

#include <iostream>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>

#include "Colours.hpp"
#include "Vector.hpp"

ALLEGRO_DISPLAY *display = nullptr;
ALLEGRO_EVENT_QUEUE *evQueue = nullptr;
ALLEGRO_TIMER *timer = nullptr;
ALLEGRO_TIMER *mouseTimer = nullptr;
ALLEGRO_TIMER *algoTimer = nullptr;
ALLEGRO_FONT *font = nullptr;
int fontHeight;

Vector screen = *(new Vector(768, 768));

bool initAllegro() {
    if (!al_init()) {
        std::cerr << "Error initializing Allegro" << std::endl;
        return false;
    }
    if (!al_init_font_addon()) {
        std::cerr << "Error initializing Allegro font addon" << std::endl;
        return false;
    }

    if (!al_init_ttf_addon()) {
        std::cerr << "Error initializing Allegro TrueType addon" << std::endl;
        return false;
    }

    if (!al_init_primitives_addon()) {
        std::cerr << "Error initializing Allegro primitives addon" << std::endl;
        return false;
    }

    if (!al_init_native_dialog_addon()) {
        std::cerr << "Error initializing Allegro native dialog addon"
            << std::endl;
        return false;
    }

    display = al_create_display(screen.x, screen.y);
    if (!display) {
        std::cerr << "Failed to initialize Allegro display" << std::endl;
        return false;
    }

    algoTimer = al_create_timer(0.01);
    if (!algoTimer) {
        std::cerr << "Failed to initialize Allegro timer" << std::endl;
        return false;
    }

    loadColours();

    return true;
}

bool loadAssets() {
    font = al_load_ttf_font(fontPath, 20, 0);
    if (!font) {
        std::cerr << "Error loading font " << fontPath << std::endl;
        return false;
    }
    fontHeight = al_get_font_line_height(font);

    return true;
}

void destroyAllegro() {
    al_destroy_font(font);
    al_destroy_timer(timer);
    al_destroy_display(display);
}
