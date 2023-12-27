#include <iostream>

/*
    ==============
    === MEDIUM ===
    ==============

    ============================================
    1523) Count Odd Numbers in an Interval Range
    ============================================

    ============
    Description:
    ============

    Given two non-negative integers low and high. Return the count of odd
    numbers between low and high (inclusive).

    ===========================================
    FUNCTION: int countOdds(int low, int high);
    ===========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: low = 3, high = 7
    Output: 3
    Explanation: The odd numbers between 3 and 7 are [3,5,7].

    --- Example 2 ---
    Input: low = 8, high = 10
    Output: 1
    Explanation: The odd numbers between 8 and 10 are [9].

    *** Constraints ***
    0 <= low <= high <= 10^9

*/

/* Time  Beats:   100% */
/* Space Beats: 77.13% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution {
public:
    int countOdds(int a, int b)
    {
        if((a & 1) && (b & 1))
            return (b - a + 2) / 2;
        else if((a & 1) || (b & 1))
            return (b - a + 1) / 2;

        return (b - a) / 2;
    }
};
