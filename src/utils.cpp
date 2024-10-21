#include "../include/utils.h"
#include <sstream>
#include <vector>

// Tokenize a document into words (simple split by space)
std::vector<std::string> tokenize(const std::string &text) {
    std::vector<std::string> tokens;
    std::istringstream stream(text);
    std::string word;
    while (stream >> word) {
        tokens.push_back(word);
    }
    return tokens;
}
