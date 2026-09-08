#ifndef TASK4_H
#define TASK4_H

#include <string>

inline int naivePatternMatch(const std::string& text, const std::string& pattern) {
    if (pattern.empty()) {
        return 0; // Empty pattern matches at index 0
    }
    int n = static_cast<int>(text.length());
    int m = static_cast<int>(pattern.length());

    for (int i = 0; i <= n - m; ++i) {
        int j = 0;
        while (j < m && text[i + j] == pattern[j]) {
            j++;
        }
        if (j == m) {
            return i; // First occurrence index found
        }
    }
    return -1; // Pattern not found
}

#endif