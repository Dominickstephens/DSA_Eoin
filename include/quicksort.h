//
// Created by Dominick on 22/10/2024.
//

#ifndef DSA_PROJECT_QUICKSORT_H
#define DSA_PROJECT_QUICKSORT_H


#include <utility>
#include "../include/IndexEntry.h"  // Include your IndexEntry definition
#include "pairImp.h"  // Include your Pair definition
#include "../include/vectorBook.h"  // Include your IndexEntry definition



// Function prototypes
void quickSort(vectorClass<Pair<IndexEntry, double>>& vec, int low, int high);
bool compareTfIdf(const Pair<IndexEntry, double>& a, const Pair<IndexEntry, double>& b);



#endif //DSA_PROJECT_QUICKSORT_H
