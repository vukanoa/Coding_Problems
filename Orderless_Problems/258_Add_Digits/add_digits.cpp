#include <iostream>

/*
    ============
    === EASY ===
    ============

    ===========================
    258) Add Digits
    ===========================

    ============
    Description:
    ============

    Given an integer num, repeatedly add all its digits until the result has
    only one digit, and return it.


    ---------------
    -- Follow Up --
    ---------------

    Could you do it without any loop/recursion in O(1) runtime?


    =================================
    FUNCTION: int addDigits(int num);
    =================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: num = 38
    Output: 2
    Explanation: The process is
    38 --> 3 + 8 --> 11
    11 --> 1 + 1 --> 2
    Since 2 has only one digit, return it.

    --- Example 2 ---
    Input: num = 0
    Output: 0


    *** Constraints ***
    0 <= num <= 2^31 - 1

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  15.79% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution {
public:
    int addDigits(int num)
    {
        if (num < 10)
            return num;

        if (num % 9 == 0)
            return 9;

        int digit = num / 9;
        digit = 9 * digit;
        digit = num - digit;

        return digit;
    }
};
