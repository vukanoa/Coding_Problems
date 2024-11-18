#include <iostream>

/*
    ============
    === EASY ===
    ============

    ===========================
    507) Perfect Number
    ===========================

    ============
    Description:
    ============

    A perfect number is a positive integer that is equal to the sum of its
    positive divisors, excluding the number itself. A divisor of an integer x
    is an integer that can divide x evenly.

    Given an integer n, return true if n is a perfect number, otherwise return
    false.

    ===========================================
    FUNCTION: bool checkPerfectNumber(int num);
    ===========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: num = 28
    Output: true
    Explanation: 28 = 1 + 2 + 4 + 7 + 14
    1, 2, 4, 7, and 14 are all divisors of 28.


    --- Example 2 ---
    Input: num = 7
    Output: false


    *** Constraints ***
    1 <= num <= 10^8

*/

/*
    ------------
    --- IDEA ---
    ------------

    Self-Explnatory.

*/

/* Time  Beats: 27.28% */
/* Space Beats: 56.30% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Brute_Force {
public:
    bool checkPerfectNumber(int num)
    {
        int sum = 0;

        for (int div = 1; div < num; div++)
        {
            if (num % div == 0)
                sum += div;
        }

        return sum == num;
    }
};
