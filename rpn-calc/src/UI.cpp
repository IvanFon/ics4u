/**
 * @file UI.cpp
 * @brief User interface
 * @author Ivan Fonseca
 * @copyright GPL-3.0
 */

/// @todo use current input instead of two from top of stack

#include "UI.hpp"

#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>

#include "Colours.hpp"
#include "Init.hpp"
#include "RPNStack.hpp"
#include "Vector.hpp"

// Button size
const Vector btnSize = *(new Vector(70, 75));
// Display height
const int dispHeight = 125;
// Text
const std::vector<std::vector<std::string>> btnText = {
    { "C", "AC", "del", "÷", "a^b" },
    { "7", "8", "9", "×", "b√a" },
    { "4", "5", "6", "−", "pop" },
    { "1", "2", "3", "+", "swap" },
    { "0", ".", "+/-", "=1", "=2" }
};
// Button mouse over fade
std::vector<std::vector<double>> btnFade(
    btnText.size(), std::vector<double>(btnText[0].size(), 100.0));
// Amount of fade
const unsigned short fadeAmnt = 90;
// Amount of fade when clicked
const unsigned short clickFadeAmnt = 75;
// Fade speed
const unsigned short fadeSpd = 1;
// Number of buttons
const Vector numBtns = *(new Vector(btnText.size(), btnText[0].size()));

void drawUI(RPNStack stack, const std::string &curIn,
    const Vector &pos, const bool mousePressed) {
    drawButtons(pos, mousePressed);

    // Draw stack
    std::stringstream stackDisplay;
    stackDisplay << "Stack: ";
    if (stack.getTop() >= 0) {
        stackDisplay << stack.displayAll();
    } else {
        stackDisplay << "empty";
    }
    al_draw_text(medFont, COL_MED_TEXT, 20, 15, 0, stackDisplay.str().c_str());

    // Draw current input
    al_draw_text(bigFont, COL_WHITE, screen.x - 25, 85 - smallFontHeight,
        ALLEGRO_ALIGN_RIGHT, curIn.c_str());
}

void drawButtons(const Vector &pos, const bool mousePressed) {
    // Button background
    al_draw_filled_rectangle(0, 126, screen.x, screen.y, COL_FORE);

    // Vertical lines
    for (int i = 1; i <= (numBtns.x); i++) {
        al_draw_line(i * 70, 0, i * 70, screen.y, COL_BACK, 2);
    }
    // Horizontal lines
    for (int i = 1; i <= (numBtns.y - 1); i++) {
        al_draw_line(0, dispHeight + (i * 75), screen.x,  dispHeight + (i * 75),
            COL_BACK, 2);
    }

    // Get enter button fade
    double enterFade = std::min(btnFade[4][3], btnFade[4][4]);

    // Button fade
    for (int y = 0; y < numBtns.y; y++) {
        for (int x = 0; x < numBtns.x; x++) {
            // Check if mouse is on button
            if (pos.x >= (x * btnSize.x) &&
            pos.x <= (x * btnSize.x) + btnSize.x &&
            pos.y >= (y * btnSize.y) + dispHeight &&
            pos.y <= (y * btnSize.y) + btnSize.y + dispHeight) {
                btnFade[y][x] = (mousePressed) ? clickFadeAmnt : fadeAmnt;
            }
            if (btnFade[y][x] != 100) {
                // Choose colour
                ALLEGRO_COLOR tmpFadeCol = al_map_rgb(
                    COL_FORE_R * btnFade[y][x] / 100,
                    COL_FORE_G * btnFade[y][x] / 100,
                    COL_FORE_B * btnFade[y][x] / 100);
                al_draw_filled_rectangle(
                    x * btnSize.x, dispHeight + (y * btnSize.y),
                    (x * btnSize.x) + btnSize.x,
                    dispHeight + (y * btnSize.y) + btnSize.y,
                    tmpFadeCol);
                // Fade back
                if (btnFade[y][x] < 100.0) {
                    btnFade[y][x] += fadeSpd;
                }
            }
        }
    }

    // Button text
    for (unsigned int y = 0; y < btnText.size(); y++) {
        for (unsigned int x = 0; x < btnText[y].size(); x++) {
            // Choose text colour and font
            ALLEGRO_COLOR colour = COL_WHITE;
            ALLEGRO_FONT *font = smallFont;
            if (btnText[y][x] == "C" || btnText[y][x] == "AC") {
                colour = COL_RED;
                font = smallHeavyFont;
            }
            al_draw_text(font, colour,
                (btnSize.x * x) + (btnSize.x / 2),
                dispHeight + (btnSize.y * y) + smallFontHeight,
                ALLEGRO_ALIGN_CENTER, btnText[y][x].c_str());
            // Enter button
            if (btnText[y][x] == "=2") {
                ALLEGRO_COLOR tmpFadeCol = al_map_rgb(
                    COL_FORE_R * enterFade / 100,
                    COL_FORE_G * enterFade / 100,
                    COL_FORE_B * enterFade / 100);
                al_draw_filled_rectangle(
                    (x - 1) * btnSize.x, dispHeight + (y * btnSize.y),
                    (x + 1) * btnSize.x,
                    dispHeight + (y * btnSize.y) + btnSize.y,
                    tmpFadeCol);
                al_draw_text(font, colour,
                    btnSize.x * x,
                    dispHeight + (y * btnSize.y) + smallFontHeight,
                    ALLEGRO_ALIGN_CENTER, "Enter");
            }
        }
    }
}

void clickButton(RPNStack &stack, std::string &curIn,
    bool &negative, const Vector &pos) {
    // Loop through buttons
    for (int y = 0; y < int(btnText.size()); y++) {
        for (int x = 0; x < int(btnText[y].size()); x++) {
            // Check if this button was pressed
            if (pos.x >= (x * btnSize.x) &&
                pos.x <= (x * btnSize.x) + btnSize.x &&
                pos.y >= (y * btnSize.y) + dispHeight &&
                pos.y <= (y * btnSize.y) + btnSize.y + dispHeight) {
                // Fade
                btnFade[y][x] = clickFadeAmnt;
                switch (y) {
                    case 0:
                        switch (x) {
                            case 0:
                                // C
                                curIn = "";
                                break;
                            case 1:
                                // AC
                                stack.clear();
                                curIn = "";
                                break;
                            case 2:
                                // Del
                                curIn = curIn.substr(0, curIn.length() - 1);
                                break;
                            case 3:
                                // /
                                if (!stack.div()) {
                                    showError("Stack must have at least two items to divide"); /* NOLINT(whitespace/line_length) */
                                }
                                break;
                            case 4:
                                // a^b
                                stack.pow();
                                break;
                        }
                        break;
                    case 1:
                        switch (x) {
                            case 0:
                                // 7
                                curIn += "7";
                                break;
                            case 1:
                                // 8
                                curIn += "8";
                                break;
                            case 2:
                                // 9
                                curIn += "9";
                                break;
                            case 3:
                                // x
                                if (!stack.mul()) {
                                    showError("Stack must have at least two items to multiply"); /* NOLINT(whitespace/line_length) */
                                }
                                break;
                            case 4:
                                // b sqrt a
                                stack.root();
                                break;
                        }
                        break;
                    case 2:
                        switch (x) {
                            case 0:
                                // 4
                                curIn += "4";
                                break;
                            case 1:
                                // 5
                                curIn += "5";
                                break;
                            case 2:
                                // 6
                                curIn += "6";
                                break;
                            case 3:
                                // -
                                if (!stack.sub()) {
                                    showError("Stack must have at least two items to subtract"); /* NOLINT(whitespace/line_length) */
                                }
                                break;
                            case 4:
                                // pop
                                if (stack.getTop())
                                curIn = std::to_string(stack.pop());
                                if (curIn[0] == '-') {
                                    negative = true;
                                }
                                break;
                        }
                        break;
                    case 3:
                        switch (x) {
                            case 0:
                                // 1
                                curIn += "1";
                                break;
                            case 1:
                                // 2
                                curIn += "2";
                                break;
                            case 2:
                                // 3
                                curIn += "3";
                                break;
                            case 3:
                                // +
                                if (!stack.add()) {
                                    showError("Stack must have at least two items to add"); /* NOLINT(whitespace/line_length) */
                                }
                                break;
                            case 4:
                                // swap
                                stack.swap();
                                break;
                        }
                        break;
                    case 4:
                        switch (x) {
                            case 0:
                                // 0
                                curIn += "0";
                                break;
                            case 1:
                                // .
                                curIn += ".";
                                break;
                            case 2:
                                // +/-
                                negative = !negative;
                                if (negative) {
                                    curIn = "-" + curIn;
                                } else {
                                    curIn.erase(0, 1);
                                }
                                break;
                            case 3:
                            case 4:
                                // =
                                // Check if input isn't empty
                                if (curIn != "" || curIn != "-") {
                                    stack.push(std::stod(curIn));
                                    curIn = "";
                                }
                                break;
                        }
                        break;
                }
            }
        }
    }
}

void showError(const std::string &message) {
    al_show_native_message_box(display, "Error", "", message.c_str(), NULL,
        ALLEGRO_MESSAGEBOX_ERROR);
}
