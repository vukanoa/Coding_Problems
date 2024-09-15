#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    1291) Sequential Digits
    ===========================

    ============
    Description:
    ============

    An integer has sequential digits if and only if each digit in the number is
    one more than the previous digit.

    Return a sorted list of all the integers in the range [low, high] inclusive
    that have sequential digits.

    ==========================================================
    FUNCTION: vector<int> sequentialDigits(int low, int high);
    ==========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: low = 100, high = 300
    Output: [123,234]

    --- Example 2 ---
    Input: low = 1000, high = 13000
    Output: [1234,2345,3456,4567,5678,6789,12345]


    *** Constraints ***
    10 <= low <= high <= 10^9

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 44.80% */
/* Space Beats: 33.60% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution {
public:
    vector<int> sequentialDigits(int low, int high)
    {
        vector<int> result;
        string str = "123456789";

        int len = str.length();

        for (int i = 2; i <= len; i++) // start from 2 because low >= 10
        {
            for (int j = 0; j <= len-i; j++) // len - i = require no. of digits
            {
                string temp = str.substr(j, i);
                int num = stoi(temp);

                if (num >= low && num <= high)
                    result.push_back(num);
            }
        }

        return result;
    }
};
