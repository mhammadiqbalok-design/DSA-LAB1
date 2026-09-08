#ifndef TASK5_H
#define TASK5_H
#include <iostream>
#include <vector>
using namespace std;
inline vector<vector<int>> generatePascalsTriangle(int totalRows)
{
    vector<vector<int>> triangle;

    if (totalRows <= 0)
    {
        return triangle;
    }

    for (int i = 0; i < totalRows; i = i + 1)
    {
        vector<int> currentRow(i + 1, 1);

        for (int j = 1; j < i; j = j + 1)
        {
            currentRow[j] = triangle[i - 1][j - 1] + triangle[i - 1][j];
        }

        triangle.push_back(currentRow);
    }

    return triangle;
}

#endif