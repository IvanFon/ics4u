/**
 * @file Init.hpp
 * @brief Initialize Allegro
 * @author Ivan Fonseca
 * @license GPL-3.0
 */

#include "Init.hpp"

#include <iostream>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>

ALLEGRO_DISPLAY *display = nullptr;
ALLEGRO_EVENT_QUEUE *evQueue = nullptr;
ALLEGRO_TIMER *drawTimer = nullptr;

bool initAllegro() {
    if (!al_init()) {
        std::cerr << "Error initializing Allegro" << std::endl;
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

    evQueue = al_create_event_queue();
    if (!evQueue) {
        std::cerr << "Failed to initialize Allegro event queue" << std::endl;
        return false;
    }

    drawTimer = al_create_timer(1.0 / FPS);
    if (!drawTimer) {
        std::cerr << "Failed to initialize Allegro timer" << std::endl;
        return false;
    }

    return true;
}

void destroyAllegro() {
    al_destroy_timer(drawTimer);
    al_destroy_event_queue(evQueue);
    al_destroy_display(display);
}
