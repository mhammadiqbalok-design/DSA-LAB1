#ifndef TASK3_H
#define TASK3_H
#include <vector>

inline std::vector<int> findIndices(const std::vector<int>& arr, int key) {
    std::vector<int> indices;
    for (size_t i = 0; i < arr.size(); ++i) {
        if (arr[i] == key) {
            indices.push_back(static_cast<int>(i));
        }
    }
    return indices;
}

#endif