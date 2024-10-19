//
// Created by Dominick on 19/10/2024.
//

#include "word_operation.h"
#include <regex>
#include <string>

using namespace std;

string removePunctuationsAndLower(string& s) {
    string result;
    regex validChar("[a-zA-Z0-9]");
    for (char c : s) {
        if (regex_match(string(1, c), validChar)) { // Check if c matches the regex
            if (isalpha(c) && isupper(c)) {
                c = static_cast<char>(tolower(c));
            }
            result += c;
        }
    }
    s = result;
    return s;
}
