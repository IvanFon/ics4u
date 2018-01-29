/**
 * @file Sorts.hpp
 * @brief Sorting algorithm implementations
 * @author Ivan Fonseca
 * @copyright GPL-3.0
 */

#ifndef INC_SORTS_HPP_
#define INC_SORTS_HPP_

#include <vector>

/// @brief Check if a vector is sorted
/// @param vect Vector to check
/// @return True if sorted, false otherwise
bool sorted(std::vector<int> &vect);

/// @brief Shuffle a vector
/// @param vect Vector to shuffle
void shuffle(std::vector<int> &vect);

/// @brief Bubble sort a vector
/// @param vect Vector to sort
/// @return Number of swaps
int bubbleSort(std::vector<int> &vect);

/// @brief Selection sort a vector
/// @param vect Vector to sort
/// @return Number of swaps
int selectionSort(std::vector<int> &vect);

/// @brief Insertion sort a vector
/// @param vect Vector to sort
/// @return Number of swaps
int insertionSort(std::vector<int> &vect);

/// @brief Merge sort a vector
/// @param vect Vector to sort
int mergeSort(std::vector<int> &vect);

/// @brief Merge two halves of vector
/// @param vect Vector to merge into
/// @param left Left half
/// @param right Right half
/// @param swaps Number of swaps
void merge(std::vector<int> &vect,
    std::vector<int> &left, std::vector<int> &right, int &swaps);

/// @brief Quick sort wrapper
/// @param vect Vector to sort
/// @return Number of swaps
int quickSortWrapper(std::vector<int> &vect);

/// @brief Quick sort vector
/// @param vect Vector to sort
/// @param left Leftmost bound of vector to sort
/// @param right Rightmost bound of vector to sort
/// @param swaps Swap counter
/// @return Number of swaps
int quickSort(std::vector<int> &vect, int left, int right, int &swaps);

/// @brief Partition vector
/// @param vect Vector to partition
/// @param left Leftmost bound of vector to partition
/// @param right Rightmost bound of vector to partition
/// @param swaps Swap counter
/// @return Middle
int partition(std::vector<int> &vect, int left, int right, int &swaps);

#endif  // INC_SORTS_HPP_

