/**
 * @file main.cpp
 * @brief Initialization and main loop
 * @author Ivan Fonseca
 * @copyright GPL-3.0
 */

#include <iostream>
#include <string>

#include <allegro5/allegro.h>

#include "Colours.hpp"
#include "Init.hpp"
#include "UI.hpp"

int main() {
    if (!initAllegro()) {
        return 1;
    }

    if (!loadAssets()) {
        return 1;
    }

    // Create stack
    RPNStack stack;
    // Current number
    std::string curIn = "";
    // If current number is negative
    bool negative = false;

    // Event sources
    al_register_event_source(evQueue, al_get_display_event_source(display));
    al_register_event_source(evQueue, al_get_timer_event_source(timer));
    al_register_event_source(evQueue, al_get_timer_event_source(mouseTimer));
    al_register_event_source(evQueue, al_get_keyboard_event_source());
    al_register_event_source(evQueue, al_get_mouse_event_source());

    // Clear display
    al_clear_to_color(COL_BACK);
    al_flip_display();

    bool running = true;
    bool redraw = true;
    al_start_timer(timer);
    al_start_timer(mouseTimer);
    while (running) {
        // Get events
        ALLEGRO_EVENT event;
        ALLEGRO_TIMEOUT timeout;
        al_init_timeout(&timeout, 0.06);
        al_wait_for_event_until(evQueue, &event, &timeout);

        switch (event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                running = false;
                break;
            case ALLEGRO_EVENT_TIMER:
                redraw = true;
                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
                clickButton(stack, curIn, negative,
                    Vector(event.mouse.x, event.mouse.y));
                break;
            case ALLEGRO_EVENT_KEY_DOWN:
                if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                    running = false;
                }
                break;
        }

        // Draw
        if (redraw && al_event_queue_is_empty(evQueue)) {
            redraw = false;
            al_clear_to_color(COL_BACK);
            // Get mouse position
            ALLEGRO_MOUSE_STATE mouseState;
            al_get_mouse_state(&mouseState);
            // Draw UI
            drawUI(stack, curIn, Vector(
                al_get_mouse_state_axis(&mouseState, 0),
                al_get_mouse_state_axis(&mouseState, 1)),
                al_mouse_button_down(&mouseState, 1));
            al_flip_display();
        }
    }

    destroyAllego();

    return 0;
}
