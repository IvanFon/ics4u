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
#include <allegro5/allegro_primitives.h>

#include "Draw.hpp"

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
    textFont = al_load_ttf_font("fonts/roboto/Roboto-Regular.ttf", 16, 0);
    if (!titleFont || !textFont) {
        std::cerr << "Error loading fonts" << std::endl;
        return false;
    }
    return true;
}

void drawUI(const std::string &filename,
    const int fileWidth, const int fileHeight,
    const ALGORITHM algo,
    const bool drawMap, const bool drawPaths, const bool drawBestPath) {
    // White
    ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);
    // Pressed button colour
    ALLEGRO_COLOR green = al_map_rgb(0, 255, 0);
    // Draw title
    std::stringstream title;
    title << filename << " (" << fileWidth << "x" << fileHeight << ")";
    al_draw_text(titleFont, white,
        (fileWidth) / 2, 4, ALLEGRO_ALIGN_CENTRE,
        title.str().c_str());

    // Normal algorithm button
    al_draw_rounded_rectangle(
        fileWidth + (settingsWidth / 16),
        titleHeight,
        fileWidth + (settingsWidth / 2) - (settingsWidth / 16),
        titleHeight + 56, 5, 5,
        (algo == NORMAL) ? green : white, 3);

    // Normal algorithm text
    al_draw_text(textFont, white,
        fileWidth + (settingsWidth / 4),
        titleHeight + 8,
        ALLEGRO_ALIGN_CENTRE, "Normal");
    al_draw_text(textFont, white,
        fileWidth + (settingsWidth / 4),
        titleHeight + 28,
        ALLEGRO_ALIGN_CENTRE, "Algorithm");

    // Downhill algorithm button
    al_draw_rounded_rectangle(
        fileWidth + (settingsWidth / 2) + (settingsWidth / 16),
        titleHeight,
        fileWidth + settingsWidth - (settingsWidth / 16),
        titleHeight + 56, 5, 5,
        (algo == DOWNHILL) ? green : white, 3);

    // Downhill algorithm text
    al_draw_text(textFont, white,
        fileWidth + (settingsWidth / 2) + (settingsWidth / 4),
        titleHeight + 8,
        ALLEGRO_ALIGN_CENTRE, "Downhill");
    al_draw_text(textFont, white,
        fileWidth + (settingsWidth / 2) + (settingsWidth / 4),
        titleHeight + 28,
        ALLEGRO_ALIGN_CENTRE, "Algorithm");

    // Draw map button
    al_draw_rounded_rectangle(
        fileWidth + (settingsWidth / 16),
        titleHeight + 112,
        fileWidth + (settingsWidth / 2) - (settingsWidth / 16),
        titleHeight + 168, 5, 5,
        (drawMap) ? green : white, 3);
    // Draw map text
    al_draw_text(textFont, white,
        fileWidth + (settingsWidth / 4),
        titleHeight + 120,
        ALLEGRO_ALIGN_CENTRE, "Toggle");
    al_draw_text(textFont, white,
        fileWidth + (settingsWidth / 4),
        titleHeight + 140,
        ALLEGRO_ALIGN_CENTRE, "Map");

    // Draw paths button
    al_draw_rounded_rectangle(
        fileWidth + (settingsWidth / 2) + (settingsWidth / 16),
        titleHeight + 112,
        fileWidth + settingsWidth - (settingsWidth / 16),
        titleHeight + 168, 5, 5,
        (drawPaths) ? green : white, 3);
    // Draw paths text
    al_draw_text(textFont, white,
        fileWidth + (settingsWidth / 2) + (settingsWidth / 4),
        titleHeight + 120,
        ALLEGRO_ALIGN_CENTRE, "Toggle");
    al_draw_text(textFont, white,
        fileWidth + (settingsWidth / 2) + (settingsWidth / 4),
        titleHeight + 140,
        ALLEGRO_ALIGN_CENTRE, "Paths");

    // Draw best path button
    al_draw_rounded_rectangle(
        fileWidth + (settingsWidth / 16),
        titleHeight + 192,
        fileWidth + (settingsWidth / 2) - (settingsWidth / 16),
        titleHeight + 248, 5, 5,
        (drawBestPath) ? green : white, 3);
    al_draw_text(textFont, white,
        fileWidth + (settingsWidth / 4),
        titleHeight + 200,
        ALLEGRO_ALIGN_CENTRE, "Toggle");
    al_draw_text(textFont, white,
        fileWidth + (settingsWidth / 4),
        titleHeight + 220,
        ALLEGRO_ALIGN_CENTRE, "Best Path");
}
