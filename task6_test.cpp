#include <iostream>
#include <vector>
#include "task6.h"

using namespace std;

void printModes(string testName, vector<int> modes)
{
    cout << testName << ": [ ";
    for (int i = 0; i < modes.size(); i = i + 1)
    {
        cout << modes[i] << " ";
    }
    cout << "]" << endl;
}

int main()
{
    // Test 1: Unique mode
    vector<int> test1 = {1, 3, 3, 3, 2, 5};
    printModes("Test 1 (Unique mode)", findMode(test1));

    // Test 2: Multiple modes
    vector<int> test2 = {1, 2, 2, 3, 3, 4};
    printModes("Test 2 (Multiple modes)", findMode(test2));

    // Test 3: Empty array
    vector<int> test3 = {};
    printModes("Test 3 (Empty array)", findMode(test3));

    return 0;
}