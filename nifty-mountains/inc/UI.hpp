/**
 *  @file UI.hpp
 *  @brief UI
 *  @author Ivan Fonseca
 */

#ifndef INC_UI_HPP_
#define INC_UI_HPP_

#include <string>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

/// @brief Title text font
extern ALLEGRO_FONT *titleFont;
/// @brief Normal text font
extern ALLEGRO_FONT *textFont;
/// @brief Title header height
extern const int titleHeight;
/// @brief Settings panel width
extern const int settingsWidth;

/// @brief Get filename
/// @param filepath Path to file
/// @param filename Name of file
/// @return true on success, false otherwise
bool getFilename(std::string &filepath, std::string &filename);

/// @brief Load fonts
/// @return true on success, false otherwise
bool loadFonts();

/// @brief Draws user interface
/// @param filename Name of file
/// @param fileWidth Width of file
/// @param fileHeight Height of file
void drawUI(const std::string &filename, const int fileWidth, const int fileHeight);

#endif  // INC_UI_HPP_
