#include <iostream>
#include <vector>

/*
    ============
    === EASY ===
    ============

    ===========================
    263) Ugly Number
    ===========================

    ============
    Description:
    ============

    An ugly number is a positive integer whose prime factors are limited to 2,
    3, and 5.

    Given an integer n, return true if n is an ugly number.

    =============================
    FUNCTION: bool isUgly(int n);
    =============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 6
    Output: true
    Explanation: 6 = 2 × 3

    --- Example 2 ---
    Input: n = 1
    Output: true
    Explanation: 1 has no prime factors, therefore all of its prime factors are
    limited to 2, 3, and 5.

    --- Example 3 ---
    Input: n = 14
    Output: false
    Explanation: 14 is not ugly since it includes the prime factor 7.


    *** Constraints ***
    -2^31 <= n <= 2^31 - 1

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  36.75% */

/* Time  Complexity: O(log2(n)) */ // Probably, not sure
/* Space Complexity: O(1)       */
class Solution {
public:
    bool isUgly(int n)
    {
        if (n <= 0)
            return false;

        std::vector<int> allowed_primes = {2, 3, 5};

        for (int& prime : allowed_primes)
        {
            while (n % prime == 0)
                n = n / prime;
        }

        return n == 1;
    }
};
