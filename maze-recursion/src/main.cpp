/**
 * @file main.cpp
 * @brief Entry point
 * @author Ivan Fonseca
 * @license GPL-3.0
 */

#include <iostream>

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>

#include "Init.hpp"
#include "Maze.hpp"
#include "UI.hpp"
#include "Vector.hpp"

int main() {
    // Initialize Allegro
    if (!initAllegro()) {
        std::cerr << "Failed to initialize Allegro" << std::endl;
        return 1;
    }

    // Get file
    std::string filepath;
    if (!getFile(filepath)) {
        std::cerr << "Error getting file" << std::endl;
        destroyAllegro();
        return 1;
    }
    // Load maze
    Maze maze(filepath);

    // Get maze size
    Vector mazeSize(maze.cols * Maze::TILE_SIZE, maze.rows * Maze::TILE_SIZE);
    // Create display
    display = al_create_display(mazeSize.x, mazeSize.y);
    if (!display) {
        std::cerr << "Error creating display" << std::endl;
        destroyAllegro();
        return 1;
    }

    // Create bitmap
    ALLEGRO_BITMAP *mazeBitmap = al_create_bitmap(mazeSize.x, mazeSize.y);
    if (!mazeBitmap) {
        std::cerr << "Error creating bitmap" << std::endl;
        destroyAllegro();
        return 1;
    }

    // Make start open
    maze.maze[maze.start.y][maze.start.x] = '.';
    // Find solution
    bool solvable = maze.findPath(maze.start.x, maze.start.y);
    // Put start back
    maze.maze[maze.start.y][maze.start.x] = 'S';
    // Draw maze
    maze.draw(mazeBitmap);
    // Show message if unsolvable
    if (!solvable) {
        al_show_native_message_box(display, "Maze unsolvable", "Maze unsolvable", "", NULL, ALLEGRO_MESSAGEBOX_ERROR);
    }

    // Event sources
    al_register_event_source(evQueue, al_get_display_event_source(display));
    al_register_event_source(evQueue, al_get_timer_event_source(drawTimer));

    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_flip_display();
    al_start_timer(drawTimer);
    bool redraw = true;
    bool running = true;
    // Game loop
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
        }

        // Draw
        if (redraw && al_is_event_queue_empty(evQueue)) {
            redraw = false;
            // Clear screen
            al_clear_to_color(al_map_rgb(0, 0, 0));
            // Draw map
            al_draw_bitmap(mazeBitmap, 0, 0, 0);

            al_flip_display();
        }
    }

    destroyAllegro();

    return 0;
}