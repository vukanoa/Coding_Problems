#include <iostream>

/*
    ==============
    === MEDIUM ===
    ==============

    =================================
    201) Bitwise AND of Numbers Range
    =================================

    ============
    Description:
    ============

    Given two integers left and right that represent the range [left, right],
    return the bitwise AND of all numbers in this range, inclusive.

    ===================================================
    FUNCTION: int rangeBitwiseAnd(int left, int right);
    ===================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: left = 5, right = 7
    Output: 4

    --- Example 2 ---
    Input: left = 0, right = 0
    Output: 0

    --- Example 3 ---
    Input: left = 1, right = 2147483647
    Output: 0


    *** Constraints ***
    0 <= left <= right <= 2^31 - 1

*/

/*
    ------------
    --- IDEA ---
    ------------

    The answer is the common prefix of left and right in their binary
    representation:

    For example:
        0b0101 (left)
        0b0111 (right)
        0b0100 (answer)

    In a nutshell:
        Keep shifting right to find the common prefix

*/

/* Time  Beats: 81.50% */
/* Space Beats: 79.74% */

/* Time  Complexity: O(log(min(left, right))) */
/* Space Complexity: O(1) */
class Solution {
public:
    int rangeBitwiseAnd(int left, int right)
    {
        int shifts = 0;
        while (right != left)
        {
            right >>= 1;
            left  >>= 1;

            shifts++;
        }

        return left << shifts;
    }
};
