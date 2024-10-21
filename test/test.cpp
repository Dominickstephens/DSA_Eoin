//
// Created by Dominick on 19/10/2024.
//

#include <iostream>
#include <cassert>  // Include for assert

using namespace std;

// Example function to test
int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

// Simple test for the add function
void test_add() {
    assert(add(2, 3) == 5);  // Test should pass
    assert(add(-1, 1) == 0); // Test should pass
}

// Test subtraction function
void test_subtract() {
    assert(subtract(2, 3) == -1); // Test should pass
    assert(subtract(-1, 1) == -2); // Test should pass
}

int main() {
    test_add();      // Run the add tests
    test_subtract(); // Run the subtract tests

    cout << "All tests passed!" << endl; // If no assert failed, this will execute
    return 0; // Return success
}
