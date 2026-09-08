#include <iostream>
#include <vector>
#include "task3.h"

void printResult(const std::string& label, const std::vector<int>& result) {
    std::cout << label << ": [ ";
    for (int val : result) {
        std::cout << val << " ";
    }
    std::cout << "]\n";
}

int main() {
    // Test 1: Multiple occurrences
    std::vector<int> arr1 = {10, 20, 30, 20, 40, 20};
    printResult("Test 1 (Multiple occurrences)", findIndices(arr1, 20));

    // Test 2: Key not present
    std::vector<int> arr2 = {5, 10, 15};
    printResult("Test 2 (Key not present)", findIndices(arr2, 99));

    // Test 3: Empty array
    std::vector<int> arr3 = {};
    printResult("Test 3 (Empty array)", findIndices(arr3, 10));

    return 0;
}