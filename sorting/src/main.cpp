/**
 * @file main.cpp
 * @brief Initialization and main loop
 * @author Ivan Fonseca
 * @copyright GPL-3.0
 */

/// @todo fix merge sort display & swap counter
/// @todo make quicksort display smoother

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <random>
#include <string>
#include <sstream>
#include <vector>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

#include "Colours.hpp"
#include "Draw.hpp"
#include "Init.hpp"
#include "Sorts.hpp"

int main() {
    if (!initAllegro()) {
        return 1;
    }

    if (!loadAssets()) {
        return 1;
    }

    loadColours();

    // Generate array
    std::vector<int> nums;
    for (int i = 1; i <= screen.x; i++) {
        nums.push_back(i);
    }

    // Clear display
    al_clear_to_color(COL_BLACK);
    al_flip_display();

    // Shuffle array
    shuffle(nums);

    // Bubble sort
    al_start_timer(algoTimer);
    int bubbleSortSwaps = bubbleSort(nums);
    al_stop_timer(algoTimer);
    int bubbleSortTime = al_get_timer_count(algoTimer);

    // Shuffle array
    shuffle(nums);

    // Selection sort
    al_set_timer_count(algoTimer, 0);
    al_start_timer(algoTimer);
    int selectionSortSwaps = selectionSort(nums);
    al_stop_timer(algoTimer);
    int selectionSortTime = al_get_timer_count(algoTimer);

    // Shuffle array
    shuffle(nums);

    // Insertion sort
    al_set_timer_count(algoTimer, 0);
    al_start_timer(algoTimer);
    int insertionSortSwaps = insertionSort(nums);
    al_stop_timer(algoTimer);
    int insertionSortTime = al_get_timer_count(algoTimer);

    // Shuffle array
    shuffle(nums);

    // Merge sort
    al_set_timer_count(algoTimer, 0);
    al_start_timer(algoTimer);
    int mergeSortSwaps = mergeSort(nums);
    al_stop_timer(algoTimer);
    int mergeSortTime = al_get_timer_count(algoTimer);

    // Shuffle array
    shuffle(nums);

    // Quicksort
    al_set_timer_count(algoTimer, 0);
    al_start_timer(algoTimer);
    int quickSortSwaps = quickSortWrapper(nums);
    al_stop_timer(algoTimer);
    int quickSortTime = al_get_timer_count(algoTimer);

    // Print results
    std::cout << "RESULTS" << std::endl;
    std::cout << "=======" << std::endl << std::endl;

    std::cout << "Bubble sort" << std::endl;
    std::cout << "-----------" << std::endl;
    std::cout << "Time: " << std::setprecision(3) <<
        (bubbleSortTime / 100.0) << std::endl;
    std::cout << "Swaps: " << bubbleSortSwaps << std::endl << std::endl;

    std::cout << "Selection sort" << std::endl;
    std::cout << "-----------" << std::endl;
    std::cout << "Time: " << std::setprecision(3) <<
        (selectionSortTime / 100.0) << std::endl;
    std::cout << "Swaps: " << selectionSortSwaps << std::endl << std::endl;

    std::cout << "Insertion sort" << std::endl;
    std::cout << "-----------" << std::endl;
    std::cout << "Time: " << std::setprecision(3) <<
        (insertionSortTime / 100.0) << std::endl;
    std::cout << "Swaps: " << insertionSortSwaps << std::endl << std::endl;

    std::cout << "Merge sort" << std::endl;
    std::cout << "-----------" << std::endl;
    std::cout << "Time: " << std::setprecision(3) <<
        (mergeSortTime / 100.0) << std::endl;
    std::cout << "Swaps: " << mergeSortSwaps << std::endl << std::endl;

    std::cout << "Quicksort" << std::endl;
    std::cout << "-----------" << std::endl;
    std::cout << "Time: " << std::setprecision(3) <<
        (quickSortTime / 100.0) << std::endl;
    std::cout << "Swaps: " << quickSortSwaps << std::endl << std::endl;


    destroyAllegro();

    return 0;
}
