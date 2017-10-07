/**
 *  @file main.cpp
 *  @brief Entry point
 *  @author Ivan Fonseca
 */

#include <iostream>
#include <string>

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
    // Initialize Allegro
    if (!initAllegro()) {
        std::cerr << "Error initializing Allegro and Allegro addons"
            << std::endl;
            return 1;
    }

    // GET INPUT

    // Get input file path and name
    std::string filepath;
    std::string filename;
    if (!getFilename(filepath, filename)) {
        std::cerr << "Error getting filename" << std::endl;
        return 1;
    }

    // Read file into matrix
    apmatrix<int> matrix(0, 0, 0);
    if (!readFile(filepath, matrix)) {
        std::cerr << "Error reading in file" << std::endl;
        return 1;
    }

    // Get map dimensions
    int mapWidth = matrix.numcols();
    int mapHeight = matrix.numrows();

    // Get minimum and maximum values of matrix
    int mapMin = matrixMin(matrix);
    int mapMax = matrixMax(matrix);

    // INITIALIZE ALLEGRO OBJECTS

    // Load fonts
    if (!loadFonts()) {
        std::cerr << "Error loading fonts" << std::endl;
        return 1;
    }

    // Create display
    ALLEGRO_DISPLAY *display = al_create_display(
        mapWidth + settingsWidth, mapHeight + titleHeight);
    if (!display) {
        std::cerr << "Error creating display" << std::endl;
        return 1;
    }

    // Create timer
    ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);
    if (!timer) {
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
    ALLEGRO_BITMAP *mapBitmap = al_create_bitmap(
        mapWidth, mapHeight);
    ALLEGRO_BITMAP *colouredMapBitmap = al_create_bitmap(
        mapWidth, mapHeight);
    ALLEGRO_BITMAP *normalPathsBitmap = al_create_bitmap(
        mapWidth, mapHeight);
    ALLEGRO_BITMAP *normalBestPathBitmap = al_create_bitmap(
        mapWidth, mapHeight);
    ALLEGRO_BITMAP *downhillPathsBitmap = al_create_bitmap(
        mapWidth, mapHeight);
    ALLEGRO_BITMAP *downhillBestPathBitmap = al_create_bitmap(
        mapWidth, mapHeight);
    if (!mapBitmap || !normalPathsBitmap || !normalBestPathBitmap ||
        !downhillPathsBitmap || !downhillBestPathBitmap) {
        std::cerr << "Error creating bitmaps" << std::endl;
        al_destroy_display(display);
        al_destroy_timer(timer);
        al_destroy_event_queue(evQueue);
        return 1;
    }

    // Event sources
    al_register_event_source(evQueue, al_get_display_event_source(display));
    al_register_event_source(evQueue, al_get_timer_event_source(timer));
    al_register_event_source(evQueue, al_get_mouse_event_source());

    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_flip_display();
    al_start_timer(timer);
    bool redraw = true;

    // Draw map and save to bitmap
    al_set_target_bitmap(mapBitmap);
    drawMatrix(matrix, mapMin, mapMax, false);
    al_set_target_bitmap(colouredMapBitmap);
    drawMatrix(matrix, mapMin, mapMax, true);
    // Set drawing target back to display
    al_set_target_bitmap(al_get_backbuffer(display));

    // Draw paths with normal algorithm to bitmaps
    drawAllPaths(matrix, NORMAL, normalPathsBitmap, normalBestPathBitmap);
    // Draw paths with downhill algorithm to bitmaps
    drawAllPaths(matrix, DOWNHILL, downhillPathsBitmap, downhillBestPathBitmap);
    // Set drawing target back to main display
    al_set_target_bitmap(al_get_backbuffer(display));

    // If we should draw map, paths and best paths
    bool drawMap = true;
    bool mapColours = false;
    bool drawPaths = true;
    bool drawBestPath = true;
    // Current algorithm
    ALGORITHM curAlgo = NORMAL;

    // Game loop
    bool running = true;
    while (running) {
        // Get events
        ALLEGRO_EVENT event;
        al_wait_for_event(evQueue, &event);

        switch (event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                running = false;
                break;
            case ALLEGRO_EVENT_TIMER:
                redraw = true;
                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
                // Handle button presses
                checkButtons(event, curAlgo, mapWidth,
                    drawMap, mapColours, drawPaths, drawBestPath);
                break;
        }

        // Draw
        if (redraw && al_is_event_queue_empty(evQueue)) {
            redraw = false;
            // Clear screen
            al_clear_to_color(al_map_rgb(0, 0, 0));

            // Draw map
            if (drawMap) {
                if (mapColours) {
                    al_draw_bitmap(colouredMapBitmap, 0, titleHeight, 0);
                } else {
                    al_draw_bitmap(mapBitmap, 0, titleHeight, 0);
                }
            }
            // Draw paths
            if (drawPaths) {
                if (curAlgo == NORMAL) {
                    al_draw_bitmap(normalPathsBitmap, 0, titleHeight, 0);
                } else {
                    al_draw_bitmap(downhillPathsBitmap, 0, titleHeight, 0);
                }
            }
            // Draw best path
            if (drawBestPath) {
                if (curAlgo == NORMAL) {
                    al_draw_bitmap(normalBestPathBitmap, 0, titleHeight, 0);
                } else {
                    al_draw_bitmap(downhillBestPathBitmap, 0, titleHeight, 0);
                }
            }

            drawUI(filename, mapWidth, mapHeight, curAlgo,
                drawMap, mapColours, drawPaths, drawBestPath);

            al_flip_display();
        }
    }

    // Cleanup
    al_destroy_display(display);
    al_destroy_timer(timer);

    return 0;
}
