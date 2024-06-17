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




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 27.80% */
/* Space Beats: 91.90% */

/* Time  Complexity: O(sqrt(c)) */
/* Space Complexity: O(1)       */
class Solution_2 {
public:
    bool judgeSquareSum(int c)
    {
        for (long a = 0; a * a <= c; a++) // Iterate through all possible values of `a`
        {
            double b = sqrt(c - a * a);   // Compute `b` as the square root of `c - a^2`
            if (b == (int)b)              // Check if `b` is an integer
            {
                return true;              // If `b` is an integer, return true
            }
        }

        return false;                     // If no such pair `(a, b)` is found, return false
    }
};
