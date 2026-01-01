#include <iostream>

/*
    ============
    === EASY ===
    ============

    ===============================
    2864) Maximum Odd Binary Number
    ===============================

    ============
    Description:
    ============

    You are given a binary string s that contains at least one '1'.

    You have to rearrange the bits in such a way that the resulting binary
    number is the maximum odd binary number that can be created from this
    combination.

    Return a string representing the maximum odd binary number that can be
    created from the given combination.


    =====
    Note: Note that the resulting string can have leading zeros.:
    =====

    ==================================================
    FUNCTION: string maximumOddBinaryNumber(string s);
    ==================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "010"
    Output: "001"
    Explanation: Because there is just one '1', it must be in the last
                 position. So the answer is "001".


    --- Example 2 ---
    Input: s = "0101"
    Output: "1001"
    Explanation: One of the '1's must be in the last position. The maximum
                 number that can be made with the remaining digits is "100". So
                 the answer is "1001".


    *** Constraints ***
    1 <= s.length <= 100
    s consists only of '0' and '1'.
    s contains at least one '1'.

*/

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  38.30% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    string maximumOddBinaryNumber(string s)
    {
        const int n = s.length();

        int ones_counter = 0;
        for (const char& chr : s)
            ones_counter += (chr == '1') ? 1 : 0;

        if (ones_counter == 0)
            return s;
        else if (ones_counter == 1)
        {
            string str(n-1, '0');
            str.push_back('1');

            return str;
        }

        string str(ones_counter - 1, '1');
        int zeroes = n - ones_counter;

        for (int i = 0; i < zeroes; i++)
            str.push_back('0');

        str.push_back('1');

        return str;
    }
};
