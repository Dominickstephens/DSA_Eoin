#include "../include/utils.h"
#include "../include/pairImp.h"
#include "../include/vectorBook.h"
#include <sstream>
#include <vector>
#include <cmath>

// tokenize a document into words by splitting spaces
std::vector<std::string> tokenize(const std::string &text) {
    std::vector<std::string> tokens;
    std::istringstream stream(text);
    std::string word;
    while (stream >> word) {
        tokens.push_back(word);
    }
    return tokens;
}

int getWordCount(const std::string &text, vectorClass<Pair<string, int>> fileWordCount) {
    for (size_t i = 0; i < fileWordCount.size(); ++i) {
        if (fileWordCount[i].first == text) {
            return fileWordCount[i].second;
        } else {
            return 1;
        }
    }
}

double calculate_tf_idf(const int frequency, const int totalWords, int totalDocuments, int totalDocumentsWithWord) {
    if (totalDocumentsWithWord == 0) {
        totalDocumentsWithWord = 1;
    }
    double tf = (double) frequency / totalWords;
    double idf = log((double) totalDocuments / totalDocumentsWithWord);
    return tf * idf * 100;
}
