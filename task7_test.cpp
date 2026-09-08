#include <iostream>
#include <vector>
#include "task7.h"

using namespace std;

void printMatrix(string title, vector<vector<int>> mat)
{
    cout << title << ":" << endl;
    for (int i = 0; i < mat.size(); i = i + 1)
    {
        for (int j = 0; j < mat[i].size(); j = j + 1)
        {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main()
{
    // Test 1: 2x2 Matrix Multiplication
    vector<vector<int>> A2 = {{1, 2}, {3, 4}};
    vector<vector<int>> B2 = {{5, 6}, {7, 8}};

    vector<vector<int>> resStandard2 = standardMultiply(A2, B2);
    vector<vector<int>> resStrassen2 = strassenMultiply(A2, B2);

    printMatrix("2x2 Standard Result", resStandard2);
    printMatrix("2x2 Strassen Result", resStrassen2);

    // Test 2: 4x4 Matrix Multiplication
    vector<vector<int>> A4 = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 1, 2, 3},
        {4, 5, 6, 7}
    };

    vector<vector<int>> B4 = {
        {8, 7, 6, 5},
        {4, 3, 2, 1},
        {1, 2, 3, 4},
        {5, 6, 7, 8}
    };

    vector<vector<int>> resStandard4 = standardMultiply(A4, B4);
    vector<vector<int>> resStrassen4 = strassenMultiply(A4, B4);

    printMatrix("4x4 Standard Result", resStandard4);
    printMatrix("4x4 Strassen Result", resStrassen4);

    return 0;
}