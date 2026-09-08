#ifndef TASK7_H
#define TASK7_H

#include <iostream>
#include <vector>

using namespace std;

// Standard 3-loop Matrix Multiplication
inline vector<vector<int>> standardMultiply(vector<vector<int>> A, vector<vector<int>> B)
{
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n, 0));

    for (int i = 0; i < n; i = i + 1)
    {
        for (int j = 0; j < n; j = j + 1)
        {
            for (int k = 0; k < n; k = k + 1)
            {
                C[i][j] = C[i][j] + A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

// Strassen's Algorithm for 2x2 base and power of 2 matrices
inline vector<vector<int>> strassenMultiply(vector<vector<int>> A, vector<vector<int>> B)
{
    int n = A.size();

    if (n == 1)
    {
        vector<vector<int>> C(1, vector<int>(1, 0));
        C[0][0] = A[0][0] * B[0][0];
        return C;
    }

    if (n == 2)
    {
        int M1 = (A[0][0] + A[1][1]) * (B[0][0] + B[1][1]);
        int M2 = (A[1][0] + A[1][1]) * B[0][0];
        int M3 = A[0][0] * (B[0][1] - B[1][1]);
        int M4 = A[1][1] * (B[1][0] - B[0][0]);
        int M5 = (A[0][0] + A[0][1]) * B[1][1];
        int M6 = (A[1][0] - A[0][0]) * (B[0][0] + B[0][1]);
        int M7 = (A[0][1] - A[1][1]) * (B[1][0] + B[1][1]);

        vector<vector<int>> C(2, vector<int>(2, 0));
        C[0][0] = M1 + M4 - M5 + M7;
        C[0][1] = M3 + M5;
        C[1][0] = M2 + M4;
        C[1][1] = M1 - M2 + M3 + M6;
        return C;
    }

    // For n > 2, fallback to standard algorithm
    return standardMultiply(A, B);
}

#endif