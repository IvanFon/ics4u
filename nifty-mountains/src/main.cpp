/**
 *  @file main.cpp
 *  @brief Entry point
 *  @author Ivan Fonseca
 */

/**
 * @todo
 * - get path with least de (delta elevation)
 *  - keep track of de while doing all the paths
 *  - store every point for each, compare with current lowest de
 *  - basically the vector min thing
 * - create display before file picker so display can be parent
 * - create input for height and width
 * - add another algorithm
 * - add buttons to change what's drawn
 * - add loading and title text
 *  - load font
 */

#include <iostream>
#include <string>
#include <random>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>

#include <apmatrix.h>

#include "Draw.hpp"
#include "Matrix.hpp"
#include "Input.hpp"
#include "UI.hpp"

/// @brief Framerate
const double FPS = 60.0;

int main() {
    // Initialize random number engine
    std::random_device rd;

    // Initialize Allegro
    if (!initAllegro()) {
        std::cerr << "Error initializing Allegro and Allegro addons"
            << std::endl;
            return 1;
    }

    // GET INPUT

    // Get input filename and size
    std::string filename;
    if (!getFilename(filename)) {
        std::cerr << "Error getting filename" << std::endl;
        return 1;
    }

    int mapWidth, mapHeight;
    std::cout << "Enter input width: ";
    std::cin >> mapWidth;
    std::cout << "Enter input height: ";
    std::cin >> mapHeight;

    // Read file into matrix
    apmatrix<int> matrix(mapHeight, mapWidth, 0);
    if (!readFile(filename, matrix)) {
        std::cerr << "Error reading in file" << std::endl;
        return 1;
    }

    // Get minimum and maximum values of matrix
    int mapMin = matrixMin(matrix);
    int mapMax = matrixMax(matrix);

    // INITIALIZE ALLEGRO OBJECTS

    // Create display
    ALLEGRO_DISPLAY *display = al_create_display(640, 480);
    if (!display) {
        std::cerr << "Error creating display" << std::endl;
        return 1;
    }

    // Create timer
    ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);
    if (!time) {
        std::cerr << "Error creating timer" << std::endl;
        al_destroy_display(display);
        return 1;
    }

    // Create event queue
    ALLEGRO_EVENT_QUEUE *evQueue = al_create_event_queue();
    if (!evQueue) {
        std::cerr << "Error creating event queue" << std::endl;
        al_destroy_display(display);
        al_destroy_timer(timer);
        return 1;
    }

    // Create bitmaps
    ALLEGRO_BITMAP *mapBitmap = al_create_bitmap(mapWidth, mapHeight);
    if (!mapBitmap) {
        std::cerr << "Error creating bitmap" << std::endl;
        al_destroy_display(display);
        al_destroy_timer(timer);
        al_destroy_event_queue(evQueue);
        return 1;
    }
    ALLEGRO_BITMAP *pathBitmap = al_create_bitmap(mapWidth, mapHeight);
    if (!pathBitmap) {
        std::cerr << "rip" << std::endl;
        return 1;
    }

    // Event sources
    al_register_event_source(evQueue, al_get_display_event_source(display));
    al_register_event_source(evQueue, al_get_timer_event_source(timer));

    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_flip_display();
    al_start_timer(timer);
    bool redraw = true;

    // Draw map and save to bitmap
    al_set_target_bitmap(mapBitmap);
    drawMatrix(matrix, mapMin, mapMax);
    // Set drawing target back to display
    al_set_target_bitmap(al_get_backbuffer(display));

    // Draw paths
    /*al_set_target_bitmap(pathBitmap);
    al_clear_to_color(al_map_rgba(0, 0, 0, 0));
    for (int i = 0; i < matrix.numrows(); i++) {
        drawPath(matrix, i, rd);
    }
    al_set_target_bitmap(al_get_backbuffer(display));*/

    // Game loop
    while (true) {
        // Get events
        ALLEGRO_EVENT event;
        al_wait_for_event(evQueue, &event);

        switch (event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                break;
            case ALLEGRO_EVENT_TIMER:
                redraw = true;
                break;
        }

        // Draw
        if (redraw && al_is_event_queue_empty(evQueue)) {
            redraw = false;
            // Clear screen
            al_clear_to_color(al_map_rgb(0, 0, 0));
            // Draw map
            al_draw_bitmap(mapBitmap, 0, 0, 0);
            al_draw_bitmap(pathBitmap, 0, 0, 0);

            al_flip_display();
        }
    }
    al_flip_display();
    al_rest(20);

    // Cleanup
    al_destroy_display(display);
    al_destroy_timer(timer);

    return 0;
}
