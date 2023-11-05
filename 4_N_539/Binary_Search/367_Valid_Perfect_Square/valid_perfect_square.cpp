#include <iostream>

/*
    ============
    === EASY ===
    ============

    ===========================
    367) Valid Perfect Square
    ===========================

    ============
    Description:
    ============

    Given a positive integer num, return true if num is a perfect square or
    false otherwise.

    A perfect square is an integer that is the square of an integer. In other
    words, it is the product of some integer with itself.

    You must not use any built-in library function, such as sqrt.

    ========================================
    FUNCTION: bool isPerfectSquare(int num);
    ========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: num = 16
    Output: true
    Explanation: We return true because 4 * 4 = 16 and 4 is an integer.

    --- Example 2 ---
    Input: num = 14
    Output: false
    Explanation: We return false because 3.742 * 3.742 = 14 and 3.742 is not an
                 integer.

    *** Constraints ***
    1 <= num <= 2^31 - 1

*/

/*
    ------------
    --- IDEA ---
    ------------

    Classic Binary Search problem.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  62.03% */

/* Time  Complexity: O(logn) */
/* Space Complexity: O(1) */
class Solution {
public:
    bool isPerfectSquare(int num)
    {
        if (num == 1)
            return true;

        int left  = 0;
        int right = num;

        while (left < right)
        {
            unsigned long long mid = left + (right - left) / 2;

            if (mid * mid == num) // unsigned long long otherwise overflow
                return true;

            if (mid * mid > num)
                right = mid;
            else
                left = mid + 1;
        }

        return false;
    }
};
