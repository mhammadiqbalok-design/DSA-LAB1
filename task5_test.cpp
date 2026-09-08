#include <iostream>
#include <vector>
#include "task5.h"

using namespace std;

void printTriangle(int n, vector<vector<int>> triangle)
{
    cout << "Pascal Triangle for n = " << n << ":" << endl;
    for (int i = 0; i < triangle.size(); i = i + 1)
    {
        for (int j = 0; j < triangle[i].size(); j = j + 1)
        {
            cout << triangle[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main()
{
    // Test 1: n = 0
    vector<vector<int>> result0 = generatePascalsTriangle(0);
    printTriangle(0, result0);

    // Test 2: n = 1
    vector<vector<int>> result1 = generatePascalsTriangle(1);
    printTriangle(1, result1);

    // Test 3: n = 5
    vector<vector<int>> result5 = generatePascalsTriangle(5);
    printTriangle(5, result5);

    return 0;
}