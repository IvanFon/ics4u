/**
 * @file encryption.hpp
 * @brief Cipher algorithm
 * @author Ivan Fonseca
 * @copyright GPL-3.0
 */

#include <string>

/// @brief Encrypt a string using vignere cipher
/// @param key Key
/// @param input String to encrypt
/// @return Encrypted string
std::string encrypt(const std::string &key, std::string input);

/// @brief Decrypt a string using vignere cipher
/// @param key Key
/// @param input String to decrypt
/// @return Decrypted string
std::string decrypt(const std::string &key, std::string input);
