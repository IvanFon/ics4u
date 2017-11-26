/**
 * @file UI.cpp
 * @brief UI
 * @author Ivan Fonseca
 * @license GPL-3.0
 */

#include "UI.hpp"

#include <iostream>
#include <sstream>

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>

bool getFile(std::string &filepath) {
    // Create file picker
    ALLEGRO_FILECHOOSER *filePicker = al_create_native_file_dialog(
        "./res/data/",
        "Choose maze file...",
        "*",
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
    } else {
        std::cerr << "Error, no files picked" << std::endl;
        return false;
    }

    return true;
}
