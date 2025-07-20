/*
    ============
    === EASY ===
    ============

    =================================================
    3622) Check Divisibility by Digit Sum and Product
    =================================================

    ============
    Description:
    ============

    You are given a positive integer n. Determine whether n is divisible by the
    sum of the following two values:

        The digit sum of n (the sum of its digits).

        The digit product of n (the product of its digits).

    Return true if n is divisible by this sum; otherwise, return false.

    ========================================
    FUNCTION: bool checkDivisibility(int n);
    ========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 99
    Output: true
    Explanation:
    Since 99 is divisible by the sum (9 + 9 = 18) plus product (9 * 9 = 81) of
    its digits (total 99), the output is true.

    --- Example 2 ---
    Input: n = 23
    Output: false
    Explanation:
    Since 23 is not divisible by the sum (2 + 3 = 5) plus product (2 * 3 = 6)
    of its digits (total 11), the output is false.


    *** Constraints ***
    1 <= n <= 10^6

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  69.23% */

/* Time  Complexity: O(logN) */
/* Space Complexity: O(1)    */
class Solution {
public:
    bool checkDivisibility(int n)
    {
        int tmp = n;

        long long prod = 1LL;
        long long sum  = 0LL;
        while (tmp > 0)
        {
            int digit = tmp % 10;
            tmp /= 10;

            prod *= digit;
            sum += digit;
        }

        return n % (sum + prod) == 0;
    }
};
