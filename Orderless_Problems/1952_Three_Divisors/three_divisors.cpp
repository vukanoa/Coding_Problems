/*
    ============
    === EASY ===
    ============

    ===========================
    1952) Three Divisors
    ===========================

    ============
    Description:
    ============

    Given an integer n, return true if n has exactly three positive divisors.
    Otherwise, return false.

    An integer m is a divisor of n if there exists an integer k such that
    n = k * m.

    ==============================
    FUNCTION: bool isThree(int n);
    ==============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 2
    Output: false
    Explantion: 2 has only two divisors: 1 and 2.

    --- Example 2 ---
    Input: n = 4
    Output: true
    Explantion: 4 has three divisors: 1, 2, and 4.


    *** Constraints ***
    1 <= n <= 10^4

*/

/*
    ------------
    --- IDEA ---
    ------------

    Simple "factorization" problem.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  59.08% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    bool isThree(int n)
    {
        int total_factors = 0;

        // 'f' for "factor"
        for (int f = 1; f * f <= n; f++)
        {
            if (f * f == n)
            {
                total_factors++; // So that we do NOT count the same one twice
            }
            else if (n % f == 0)
            {
                total_factors++;
                total_factors++;
            }
        }

        return total_factors == 3;
    }
};
