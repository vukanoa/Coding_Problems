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
    Note: that the resulting string can have leading zeros. 
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

#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 42.59% */
/* Space Beats: 30.73% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    string maximumOddBinaryNumber(string s)
    {
        const int N = s.size();
        string result;
        result.reserve(N); // To prevent repeated reallocations;

        int ones = 0;
        for (const char& chr : s)
            ones += (chr == '1') ? 1 : 0;

        if (ones == 1)
            return string(N-1, '0') + '1';

        for (int i = 0; i < N; i++)
        {
            if (ones > 1)
            {
                result += '1';
                --ones;
            }
            else
            {
                if (i == N-1)
                    result += '1';
                else
                    result += '0';
            }
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 56.63% */
/* Space Beats: 21.68% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_2 {
public:
    string maximumOddBinaryNumber(string s)
    {
        int ones = 0;
        int zeroes = 0;

        for (const auto& chr : s)
        {
            if (chr == '1')
                ++ones;
            else
                ++zeroes;
        }

        return string(ones - 1, '1') + string(zeroes, '0') + '1';
    }
};
