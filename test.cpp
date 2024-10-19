#include <iostream>

// Example function to test
int add(int a, int b) {
    return a + b;
}

// Simple test for the add function
void test_add() {
    if (add(2, 3) != 5) {
        std::cerr << "Test failed: add(2, 3) != 5" << std::endl;
    } else {
        std::cout << "Test passed: add(2, 3) == 5" << std::endl;
    }

    if (add(-1, 1) != 0) {
        std::cerr << "Test failed: add(-1, 1) != 0" << std::endl;
    } else {
        std::cout << "Test passed: add(-1, 1) == 0" << std::endl;
    }
}

int main() {
    test_add();  // Run the tests
    return 0;
}
