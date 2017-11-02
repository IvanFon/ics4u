/**
 * @file UI.cpp
 * @brief User interface
 * @author Ivan Fonseca
 * @copyright GPL-3.0
 */

#include "UI.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

#include "Colours.hpp"
#include "Init.hpp"
#include "RPNStack.hpp"
#include "Vector.hpp"

// Number of buttons
const Vector numBtns = *(new Vector(4, 5));
// Button size
const Vector btnSize = *(new Vector(70, 75));
// Display height
const int dispHeight = 125;
// Text
const std::vector<std::vector<std::string>> btnText = {
    { "C", "AC", "+/-", "÷" },
    { "7", "8", "9", "×" },
    { "4", "5", "6", "−" },
    { "1", "2", "3", "+" },
    { "0", ".", "%", "=" }
};

void drawUI(RPNStack stack, const std::string &curIn) {
    drawButtons();

    // Draw stack
    std::stringstream stackDisplay;
    stackDisplay << "Stack: ";
    if (stack.getTop() >= 0) {
        /// @todo AAA just put this whole thing in the not here and see if it works
        int x = stack.getTop();
        while (x --> 0) {
            stackDisplay << stack.pop() << ", ";
        }
    } else {
        stackDisplay << "empty";
    }
    al_draw_text(medFont, COL_MED_TEXT, 20, 15, 0, stackDisplay.str().c_str());

    // Draw current input
    al_draw_text(bigFont, COL_WHITE, screen.x - 25, 75,
        ALLEGRO_ALIGN_RIGHT, curIn.c_str());
}

void drawButtons() {
    // Button background
    al_draw_filled_rectangle(0, 126, screen.x, screen.y, COL_FORE);

    // Button grid
    // Vertical lines
    for (int i = 1; i <= (numBtns.x - 1); i++) {
        al_draw_line(i * 70, 0, i * 70, screen.y, COL_BACK, 2);
    }
    // Horizontal lines
    for (int i = 1; i <= (numBtns.y - 1); i++) {
        al_draw_line(0, dispHeight + (i * 75), screen.x,  dispHeight + (i * 75),
            COL_BACK, 2);
    }

    // Button text
    for (int y = 0; y < btnText.size(); y++) {
        for (int x = 0; x < btnText[y].size(); x++) {
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
        }
    }
}

void clickButton(RPNStack &stack, std::string &curIn,
    bool &negative, const Vector &pos) {
    // Loop through buttons
    for (int y = 0; y < btnText.size(); y++) {
        for (int x = 0; x < btnText[y].size(); x++) {
            // Check if this button was pressed
            if (pos.x >= (x * btnSize.x) &&
                pos.x <= (x * btnSize.x) + btnSize.x &&
                pos.y >= (y * btnSize.y) + dispHeight &&
                pos.y <= (y * btnSize.y) + btnSize.y + dispHeight) {
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
                                // /
                                stack.div();
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
                                stack.mul();
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
                                stack.sub();
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
                                stack.add();
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
                                // %
                                /// @todo
                                break;
                            case 3:
                                // =
                                // Check if input isn't empty
                                if (curIn != "") {
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
