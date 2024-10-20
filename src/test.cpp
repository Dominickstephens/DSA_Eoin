//
// Created by Dominick on 19/10/2024.
//

#include <iostream>

// Include the headers needed for your tests
using namespace std;

// Example function to test
int add(int a, int b) {
    return a + b;
}

// Simple test for the add function
void test_add() {
    if (add(2, 3) != 5) {
        cerr << "Test failed: add(2, 3) != 5" << std::endl;
    } else {
        cout << "Test passed: add(2, 3) == 5" << std::endl;
    }

    if (add(-1, 1) != 0) {
        cerr << "Test failed: add(-1, 1) != 0" << std::endl;
    } else {
        cout << "Test passed: add(-1, 1) == 0" << std::endl;
    }
}

int main() {
    test_add();  // Run the tests
    return 0;
}