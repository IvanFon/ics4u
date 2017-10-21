/**
 * @file main.cpp
 * @brief Main
 * @author Ivan Fonseca
 * @copyright GPL-3.0
 */

#include <fstream>
#include <iostream>
#include <string>

#include "encryption.hpp"

int main() {
    std::string filename, input, key, output;
    int option = 0;

    // Get filename
    std::cout << "Enter filename: ";
    std::cin >> filename;

    // Open file
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file \"" << filename << "\"!" << std::endl;
        return 1;
    }

    // Read in values
    std::getline(file, key);
    std::getline(file, input);
    std::cout << "Key: " << key << std::endl
        << "Input string: " << input << std::endl;

    // Sanitize input
    std::string sanitized;
    for (int i = 0; i < static_cast<int>(input.length()); i++) {
        if (isalpha(input[i]) && std::isupper(input[i])) {
            sanitized.push_back(input[i]);
        }
    }

    // Get option
    while (!(option == 1 || option == 2)) {
        std::cout << "Encode (1) or decode (2)? ";
        std::cin >> option;

        switch (option) {
          case 1:
            output = encrypt(key, sanitized);
            break;
          case 2:
            output = decrypt(key, sanitized);
            break;
          default:
            std::cout << "Invalid option." << std::endl;
            break;
        }
    }

    std::cout << output << std::endl;

    // Close file
    file.close();

    return 0;
}
