#include <iostream>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    633) Sum of Square Numbers
    ===========================

    ============
    Description:
    ============

    Given a non-negative integer c, decide whether there're two integers a and
    b such that a2 + b2 = c.

    =====================================
    FUNCTION: bool judgeSquareSum(int c); 
    =====================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: c = 5
    Output: true
    Explanation: 1 * 1 + 2 * 2 = 5

    --- Example 2 ---
    Input: c = 3
    Output: false


    *** Constraints ***
    0 <= c <= 2^31 - 1

*/

/*
    ------------
    --- IDEA ---
    ------------

    Simple "Two Pointers" Technique.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  18.55% */

/* Time  Complexity: O(sqrt(c)) */
/* Space Complexity: O(1)       */
class Solution_Two_Pointers {
public:
    bool judgeSquareSum(int c)
    {
        long long left = 0;
        long long right = static_cast<long long>(sqrt(c));

        while(left <= right)
        {
            if(left * left + right * right == c)
                return true;
            else if(left * left + right * right > c)
                right--;
            else
                left++;
        }

        return false;
    }
};
