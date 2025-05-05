/*
    ============
    === EASY ===
    ============

    ===================================
    3536) Maximum Product of Two Digits
    ===================================

    ============
    Description:
    ============

    You are given a positive integer n.

    Return the maximum product of any two digits in n.

    =====
    Note: You may use the same digit twice if it appears more than once in n.
    =====

    ================================
    FUNCTION: int maxProduct(int n);
    ================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 31
    Output: 3
    Explanation:
        The digits of n are [3, 1].
        The possible products of any two digits are: 3 * 1 = 3.
        The maximum product is 3.


    --- Example 2 ---
    Input: n = 22
    Output: 4
    Explanation:
        The digits of n are [2, 2].
        The possible products of any two digits are: 2 * 2 = 4.
        The maximum product is 4.


    --- Example 3 ---
    Input: n = 124
    Output: 8
    Explanation:
        The digits of n are [1, 2, 4].
        The possible products of any two digits are: 1 * 2 = 2, 1 * 4 = 4, 2 * 4 = 8.
        The maximum product is 8.


    *** Constraints ***
    10 <= n <= 10^9

*/

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  43.75% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution {
public:
    int maxProduct(int n)
    {
        int one = 0;
        int two = 0;

        while (n > 0)
        {
            int digit = n % 10;
            n /= 10;

            if (digit >= one)
            {
                two = one;
                one = digit;
            }
            else if (digit >= two)
            {
                two = digit;
            }
        }

        return one * two;
    }
};
