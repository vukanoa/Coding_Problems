/*
    ============
    === HARD ===
    ============

    ===============================
    479) Largest Palindrome Product
    ===============================

    ============
    Description:
    ============

    Given an integer n, return the largest palindromic integer that can be
    represented as the product of two n-digits integers. Since the answer can
    be very large, return it modulo 1337.

    =======================================
    FUNCTION: int largestPalindrome(int n);
    =======================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 2
    Output: 987
    Explanation: 99 x 91 = 9009, 9009 % 1337 = 987

    --- Example 2 ---
    Input: n = 1
    Output: 9


    *** Constraints ***
    1 <= n <= 8

*/

#include <cmath>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 74.17% */
/* Space Beats: 82.12% */

/* Time  Complexity: O(10^(2n)) */
/* Space Complexity: O(1)       */
class Solution {
public:
    int largestPalindrome (int n)
    {
        if (n == 1)
            return 9;

        long upper = pow(10, n) - 1;
        long lower = pow(10, n - 1);

        for (long left = upper; left >= lower; left--)
        {
            long candidate = left;

            for (long mirrored_part = left; mirrored_part > 0; mirrored_part /= 10)
                candidate = candidate * 10 + mirrored_part % 10;

            for (long j = upper; j * j >= candidate; j--)
            {
                if (candidate % j == 0)
                    return candidate % 1337;
            }
        }

        return -1;
    }
};
