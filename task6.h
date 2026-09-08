#ifndef TASK6_H
#define TASK6_H

#include <iostream>
#include <vector>

using namespace std;

inline vector<int> findMode(vector<int> numbers)
{
    vector<int> modes;
    int totalElements = numbers.size();

    if (totalElements == 0)
    {
        return modes;
    }

    int highestFrequency = 0;

    // Step 1: Find highest frequency
    for (int i = 0; i < totalElements; i = i + 1)
    {
        int currentCount = 0;
        for (int j = 0; j < totalElements; j = j + 1)
        {
            if (numbers[i] == numbers[j])
            {
                currentCount = currentCount + 1;
            }
        }

        if (currentCount > highestFrequency)
        {
            highestFrequency = currentCount;
        }
    }

    // Step 2: Collect elements with highest frequency
    for (int i = 0; i < totalElements; i = i + 1)
    {
        int currentCount = 0;
        for (int j = 0; j < totalElements; j = j + 1)
        {
            if (numbers[i] == numbers[j])
            {
                currentCount = currentCount + 1;
            }
        }

        if (currentCount == highestFrequency)
        {
            bool alreadyAdded = false;
            for (int k = 0; k < modes.size(); k = k + 1)
            {
                if (modes[k] == numbers[i])
                {
                    alreadyAdded = true;
                }
            }

            if (alreadyAdded == false)
            {
                modes.push_back(numbers[i]);
            }
        }
    }

    return modes;
}

#endif