//
// Created by Dominick on 22/10/2024.
//

#include "../include/quicksort.h"
#include <algorithm>  // For std::swap



// Comparison function
bool compareTfIdf(const Pair<IndexEntry, double>& a, const Pair<IndexEntry, double>& b) {
    return a.second > b.second;  // Compare by TF-IDF score (double) in descending order
}

// Partition function for QuickSort
int partition(vectorClass<Pair<IndexEntry, double>>& vec, int low, int high) {
    double pivot = vec[high].second;  // Use the last element as the pivot
    int i = low - 1;  // Pointer for the smaller element

    for (int j = low; j < high; ++j) {
        // If current element is greater than or equal to pivot
        if (compareTfIdf(vec[j], vec[high])) {
            i++;  // increment index of smaller element
            std::swap(vec[i], vec[j]);  // Swap elements
        }
    }
    std::swap(vec[i + 1], vec[high]);  // Move pivot to the correct position
    return i + 1;  // Return the partitioning index
}

// QuickSort function
void quickSort(vectorClass<Pair<IndexEntry, double>>& vec, int low, int high) {
    if (low < high) {
        int pi = partition(vec, low, high);  // Partitioning index

        // Recursively sort elements before and after partition
        quickSort(vec, low, pi - 1);
        quickSort(vec, pi + 1, high);
    }
}
