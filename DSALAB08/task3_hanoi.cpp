#include <iostream>
#include <stack>
using namespace std;

// Move the legal way between two pegs (smaller disk always goes onto bigger / empty peg)
void moveDisks(stack<int>& a, stack<int>& b, char nameA, char nameB) {
    if (b.empty() || (!a.empty() && a.top() < b.top())) {
        cout << "Move disk " << a.top() << " from " << nameA << " to " << nameB << endl;
        b.push(a.top());
        a.pop();
    } else {
        cout << "Move disk " << b.top() << " from " << nameB << " to " << nameA << endl;
        a.push(b.top());
        b.pop();
    }
}

int main() {
    int n;
    cout << "Enter number of disks: ";
    cin >> n;

    stack<int> src, aux, dest;
    char s = 'A', a = 'B', d = 'C';

    // Even n: swap aux and dest roles
    if (n % 2 == 0) swap(a, d), swap(aux, dest);

    for (int i = n; i >= 1; i--) src.push(i);

    int total = (1 << n) - 1;   // 2^n - 1 moves
    for (int i = 1; i <= total; i++) {
        if (i % 3 == 1)      moveDisks(src, dest, s, d);
        else if (i % 3 == 2) moveDisks(src, aux, s, a);
        else                 moveDisks(aux, dest, a, d);
    }
    return 0;
}
