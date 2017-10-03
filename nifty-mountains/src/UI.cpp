/**
 *  @file UI.cpp
 *  @brief UI
 *  @author Ivan Fonseca
 */

#include <string>
#include <sstream>
#include <iostream>

#include <allegro5/allegro_native_dialog.h>

bool getFilename(std::string &filename) {
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

    // Get filename
    if (al_get_native_file_dialog_count(filePicker) > 0) {
        std::stringstream buffer;
        buffer << al_get_native_file_dialog_path(filePicker, 0);
        filename = buffer.str();
        std::cout << filename << std::endl;
    } else {
        std::cerr << "Error, no files picked" << std::endl;
        return false;
    }

    return true;
}
