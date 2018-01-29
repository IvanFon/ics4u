/**
 * @file Sorts.cpp
 * @brief Sorting algorithm implementations
 * @author Ivan Fonseca
 * @copyright GPL-3.0
 */

#include "Sorts.hpp"

#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

#include "Draw.hpp"

bool sorted(std::vector<int> &vect) {
    for (int i = 0; i < vect.size() - 1; i++) {
        if (vect[i] > vect[i + 1]) {
            return false;
        }
    }

    return true;
}

void shuffle(std::vector<int> &vect) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::shuffle(vect.begin(), vect.end(), mt);
}

int bubbleSort(std::vector<int> &vect) {
    bool swap = false;
    int swaps = 0;
    while (!sorted(vect)) {
        for (int i = 0; i < vect.size() - 1; i++) {
            if (vect[i] > vect[i + 1]) {
                std::swap(vect[i], vect[i + 1]);
                swap = true;
                swaps++;
            }
        }
        if (swap) {
            drawVector(vect, "Bubble Sort", swaps);
            swap = false;
        }
    }

    return swaps;
}

int selectionSort(std::vector<int> &vect) {
    int swaps = 0;
    bool swap = false;

    int end = vect.size();

    while (end > 1) {
        // Find max
        for (int max = 0, i = 1; i < end; i++) {
            if (vect[i] > vect[max]) {
                max = i;
            }

            // Swap with last
            std::swap(vect[max], vect[end - 1]);
            swap = true;
            swaps++;
        }

        if (swap) {
            drawVector(vect, "Selection Sort", swaps);
            swap = false;
        }

        end--;
    }
}

int insertionSort(std::vector<int> &vect) {
    int swaps = 0;

    for (int i = 1; i < vect.size(); i++) {
        // Get current value
        int cur = vect[i];

        // Find insertion location
        int n;
        for (n = 0; n < i; n++) {
            if (vect[n] >= cur) {
                break;
            }
        }

        // Shift elements to make space for value
        for (int j = i - 1; j >= n; j--) {
            vect[j + 1] = vect[j];
        }

        // Insert element
        vect[n] = cur;
        swaps++;
        drawVector(vect, "Insertion Sort", swaps);
    }

    return swaps;
}

int mergeSort(std::vector<int> &vect) {
    int swaps = 0;
    if (vect.size() > 1) {
        // Get halves of vector
        std::vector<int> left(vect.begin(), vect.begin() + (vect.size() / 2));
        mergeSort(left);
        std::vector<int> right(vect.begin() + (vect.size() / 2), vect.end());
        mergeSort(right);
        // Combine halves
        merge(vect, left, right, swaps);
        drawVector(vect, "Merge sort", swaps);
    }
}

void merge(std::vector<int> &vect,
    std::vector<int> &left, std::vector<int> &right, int &swaps) {
    // Clear vector being merged into
    vect.clear();

    // Loop through both left and right vectors at same time
    // iL = left vector counter
    // iR = right vector counter
    unsigned int iL, iR;
    for (iL = 0, iR = 0; iL < left.size() && iR < right.size();) {
        // Find current smaller value
        if (left[iL] <= right[iR]) {
            vect.push_back(left[iL]);
            iL++;
        } else {
            vect.push_back(right[iR]);
            iR++;
        }
        swaps++;
    }

    // Push remaining values
    for (; iL < left.size(); iL++) {
        vect.push_back(left[iL]);
        swaps++;
    }
    for (; iR < right.size(); iR++) {
        vect.push_back(right[iR]);
        swaps++;
    }
}

int quickSortWrapper(std::vector<int> &vect) {
    int swaps = 0;
    return quickSort(vect, 0, vect.size(), swaps);
}

int quickSort(std::vector<int> &vect, int left, int right, int &swaps) {
    int mid;
    if (left < right) {
        mid = partition(vect, left, right, swaps);
        quickSort(vect, left, mid, swaps);
        quickSort(vect, mid + 1, right, swaps);
    }
    drawVector(vect, "Quicksort", swaps);
    return swaps;
}

int partition(std::vector<int> &vect, int left, int right, int &swaps) {
    int x = vect[left];
    int i = left;
    int j;

    for (j = left + 1; j < right; j++) {
        if (vect[j] <= x) {
            i++;
            std::swap(vect[i], vect[j]);
            swaps++;
        }
    }

    std::swap(vect[i], vect[left]);
    swaps++;
    return i;
}

