//
// Created by Dominick on 22/10/2024.
//

#ifndef DSA_PROJECT_PAGINATION_H
#define DSA_PROJECT_PAGINATION_H

#include "../include/IndexEntry.h"
#include "pairImp.h"

void paginateResults(const vectorClass<Pair<IndexEntry, double>>& resultsVector, int itemsPerPage);
void displayPage(const vectorClass<Pair<IndexEntry, double>>& resultsVector, int currentPage, int itemsPerPage);

#endif //DSA_PROJECT_PAGINATION_H
