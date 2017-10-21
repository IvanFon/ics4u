/**
 * @file encryption.cpp
 * @brief Cipher algorithm
 * @author Ivan Fonseca
 * @copyright GPL-3.0
 */

#include "encryption.hpp"

#include <iostream>

std::string encrypt(const std::string &key, std::string input) {
    // Shift input
    for (int i = 0, k = 0; i < static_cast<int>(input.length()); ++i, ++k) {
        // Reset key length
        if (k > static_cast<int>(key.length()) - 1) {
            k = 0;
        }

        // Shift character
        input[i] += key[k] - 'A';
        // Check if it overflowed
        if (input[i] > 'Z') {
            input[i] -= 'Z' - 'A' + 1;
        }
    }

    return input;
}

std::string decrypt(const std::string &key, std::string input) {
    // Shift input
    for (int i = 0, k = 0; i < static_cast<int>(input.length()); ++i, ++k) {
        // Reset key length
        if (k > static_cast<int>(key.length()) - 1) {
            k = 0;
        }

        // Shift character
        input[i] -= key[k] - 'A';
        // Check if it overflowed
        if (input[i] < 'A') {
            input[i] += 'Z' - 'A' + 1;
        }
    }

    return input;
}
