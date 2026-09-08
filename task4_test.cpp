#include <iostream>
#include <string>
#include "task4.h"

void runTest(const std::string& label, const std::string& text, const std::string& pattern, int expected) {
    int result = naivePatternMatch(text, pattern);
    std::cout << label << " | Found at Index: " << result 
              << " | " << (result == expected ? "PASS" : "FAIL") << "\n";
}

int main() {
    std::string text = "hello world";

    // Test 1: Pattern at the beginning
    runTest("Test 1 (Pattern at beginning)", text, "hello", 0);

    // Test 2: Pattern at the end
    runTest("Test 2 (Pattern at end)", text, "world", 6);

    // Test 3: Pattern not present
    runTest("Test 3 (Pattern not present)", text, "python", -1);

    // Test 4: Empty pattern
    runTest("Test 4 (Empty pattern)", text, "", 0);

    return 0;
}