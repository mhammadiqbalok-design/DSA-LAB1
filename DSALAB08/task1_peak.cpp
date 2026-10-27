#include <iostream>
#include <vector>
using namespace std;

// Binary search on columns. Each step scans one column (n) and halves columns (log n)
// => O(n log n)
pair<int,int> findPeak(vector<vector<int>>& a) {
    int rows = a.size(), cols = a[0].size();
    int low = 0, high = cols - 1;

    while (low <= high) {
        int mid = (low + high) / 2;

        int maxRow = 0;                       // row of max element in middle column
        for (int i = 0; i < rows; i++)
            if (a[i][mid] > a[maxRow][mid]) maxRow = i;

        int left  = (mid > 0)        ? a[maxRow][mid - 1] : -1;
        int right = (mid < cols - 1) ? a[maxRow][mid + 1] : -1;

        if (a[maxRow][mid] >= left && a[maxRow][mid] >= right)
            return {maxRow, mid};
        else if (left > a[maxRow][mid])
            high = mid - 1;
        else
            low = mid + 1;
    }
    return {-1, -1};
}

int main() {
    vector<vector<int>> a = {
        {10, 8, 10, 10},
        {14, 13, 12, 11},
        {15, 9, 11, 21},
        {16, 17, 19, 20}
    };

    pair<int,int> p = findPeak(a);
    cout << "Peak at (" << p.first << ", " << p.second << ") = " << a[p.first][p.second] << endl;
    return 0;
}
