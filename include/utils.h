#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include "pairImp.h"
#include "../src/vectorBook.h"
#include "../src/IndexEntry.h"

// Function declaration for tokenizing strings
std::vector<std::string> tokenize(const std::string &text);
int getWordCount(const std::string &text, vectorClass<Pair<string, int>> fileWordCount);
double calculate_tf_idf(int frequency, int totalWords, int totalDocuments, int totalDocumentsWithWord);
#endif // UTILS_H
