#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

int N;
int dx[8] = {2, 1, -1, -2, -2, -1, 1, 2};
int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};
vector<vector<int>> board;

bool isSafe(int x, int y) {
    return x >= 0 && y >= 0 && x < N && y < N && board[x][y] == -1;
}

void printBoard() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) cout << setw(3) << board[i][j];
        cout << endl;
    }
}

// Part 1: plain backtracking (tries every move, undoes if stuck) - exponential
bool backtrack(int x, int y, int step) {
    board[x][y] = step;
    if (step == N * N - 1) return true;

    for (int k = 0; k < 8; k++) {
        int nx = x + dx[k], ny = y + dy[k];
        if (isSafe(nx, ny) && backtrack(nx, ny, step + 1)) return true;
    }
    board[x][y] = -1;   // undo
    return false;
}

// Count onward moves from a square
int degree(int x, int y) {
    int c = 0;
    for (int k = 0; k < 8; k++)
        if (isSafe(x + dx[k], y + dy[k])) c++;
    return c;
}

// Part 2: Warnsdorff's rule - always go to the square with the fewest onward moves.
// N*N steps, 8 moves x 8 checks each per step => O(N^2)
bool warnsdorff(int x, int y) {
    board[x][y] = 0;
    for (int step = 1; step < N * N; step++) {
        int best = -1, bestDeg = 9;
        for (int k = 0; k < 8; k++) {
            int nx = x + dx[k], ny = y + dy[k];
            if (isSafe(nx, ny)) {
                int d = degree(nx, ny);
                if (d < bestDeg) { bestDeg = d; best = k; }
            }
        }
        if (best == -1) return false;
        x += dx[best];
        y += dy[best];
        board[x][y] = step;
    }
    return true;
}

int main() {
    int x, y;
    cout << "Enter N: ";
    cin >> N;
    cout << "Enter start x y: ";
    cin >> x >> y;

    board.assign(N, vector<int>(N, -1));
    cout << "\nBacktracking (use small N, e.g. 5):\n";
    if (backtrack(x, y, 0)) printBoard(); else cout << "No tour\n";

    board.assign(N, vector<int>(N, -1));
    cout << "\nOptimized (Warnsdorff):\n";
    if (warnsdorff(x, y)) printBoard(); else cout << "No tour\n";
    return 0;
}
