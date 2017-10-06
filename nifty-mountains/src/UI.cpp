/**
 *  @file UI.cpp
 *  @brief UI
 *  @author Ivan Fonseca
 */

#include "UI.hpp"

#include <string>
#include <sstream>
#include <iostream>

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

ALLEGRO_FONT *titleFont = nullptr;
ALLEGRO_FONT *textFont = nullptr;
const int titleHeight = 48;
const int settingsWidth = 256;

bool getFilename(std::string &filepath, std::string &filename) {
    // Create file picker
    ALLEGRO_FILECHOOSER *filePicker = al_create_native_file_dialog(
        "./data/*",
        "Choose data file...",
        "*.dat",
        ALLEGRO_FILECHOOSER_FILE_MUST_EXIST);
    if (!filePicker) {
        std::cerr << "Error creating file picker" << std::endl;
        return false;
    }

    // Show file picker
    if (!al_show_native_file_dialog(NULL, filePicker)) {
        std::cerr << "Error showing file picker" << std::endl;
        return false;
    }

    // Check if a file was picked
    if (al_get_native_file_dialog_count(filePicker) > 0) {
        // Convert file path to string
        std::stringstream buffer;
        buffer << al_get_native_file_dialog_path(filePicker, 0);
        filepath = buffer.str();
        // Get filename
        ALLEGRO_PATH *file = al_create_path(
            al_get_native_file_dialog_path(filePicker, 0));
        filename = al_get_path_filename(file);
    } else {
        std::cerr << "Error, no files picked" << std::endl;
        return false;
    }

    return true;
}

bool loadFonts() {
    titleFont = al_load_ttf_font("fonts/roboto/Roboto-Regular.ttf", 32, 0);
    textFont = al_load_ttf_font("fonts/roboto/Roboto-Regular.ttf", 24, 0);
    if (!titleFont || !textFont) {
        std::cerr << "Error loading fonts" << std::endl;
        return false;
    }
    return true;
}

void drawUI(const std::string &filename, const int fileWidth, const int fileHeight) {  /* NOLINT(whitespace/line_length) */
    // Draw title
    std::stringstream title;
    title << filename << " (" << fileWidth << "x" << fileHeight << ")";
    al_draw_text(titleFont, al_map_rgb(255, 255, 255),
        (fileWidth) / 2, 4, ALLEGRO_ALIGN_CENTRE,
        title.str().c_str());
}
