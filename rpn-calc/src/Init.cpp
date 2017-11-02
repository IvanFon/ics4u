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
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

#include "Colours.hpp"
#include "Vector.hpp"

ALLEGRO_DISPLAY *display = nullptr;
ALLEGRO_EVENT_QUEUE *evQueue = nullptr;
ALLEGRO_TIMER *timer = nullptr;
ALLEGRO_TIMER *mouseTimer = nullptr;
ALLEGRO_FONT *smallFont = nullptr;
ALLEGRO_FONT *smallHeavyFont = nullptr;
ALLEGRO_FONT *medFont = nullptr;
ALLEGRO_FONT *bigFont = nullptr;
int smallFontHeight;

Vector screen = *(new Vector(280, 500));

bool initAllegro() {
    if (!al_init()) {
        std::cerr << "Error initializing Allegro" << std::endl;
        return false;
    }

    if (!al_install_keyboard()) {
        std::cerr << "Error initializing Allegro keyboard support" << std::endl;
        return false;
    }

    if (!al_install_mouse()) {
        std::cerr << "Error initializing Allegro mouse support" << std::endl;
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

    display = al_create_display(screen.x, screen.y);
    if (!display) {
        std::cerr << "Failed to initialize Allegro display" << std::endl;
        return false;
    }

    evQueue = al_create_event_queue();
    if (!evQueue) {
        std::cerr << "Failed to initialize Allegro event queue" << std::endl;
        return false;
    }

    timer = al_create_timer(1.0 / FPS);
    if (!timer) {
        std::cerr << "Failed to initialize Allegro timer" << std::endl;
        return false;
    }

    mouseTimer = al_create_timer(0.25);
    if (!mouseTimer) {
        std::cerr << "Failed to initialize Allegro timer" << std::endl;
        return false;
    }

    loadColours();

    return true;
}

bool loadAssets() {
    smallFont = al_load_ttf_font(smallFontPath, 20, 0);
    if (!smallFont) {
        std::cerr << "Error loading font " << smallFontPath << std::endl;
        return false;
    }
    smallFontHeight = al_get_font_line_height(smallFont);

    smallHeavyFont = al_load_ttf_font(smallHeavyFontPath, 20, 0);
    if (!smallHeavyFont) {
        std::cerr << "Error loading font " << smallHeavyFont << std::endl;
        return false;
    }

    medFont = al_load_ttf_font(medFontPath, 18, 0);
    if (!medFont) {
        std::cerr << "Error loading font " << medFontPath << std::endl;
        return false;
    }

    bigFont = al_load_ttf_font(bigFontPath, 32, 0);
    if (!bigFont) {
        std::cerr << "Error loading font " << bigFontPath << std::endl;
        return false;
    }

    return true;
}

void destroyAllego() {
    al_destroy_font(smallFont);
    al_destroy_font(bigFont);
    al_destroy_timer(timer);
    al_destroy_timer(mouseTimer);
    al_destroy_event_queue(evQueue);
    al_destroy_display(display);
}
