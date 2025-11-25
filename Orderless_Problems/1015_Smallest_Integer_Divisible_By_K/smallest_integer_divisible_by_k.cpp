/*
    ==============
    === MEDIUM ===
    ==============

    =====================================
    1015) Smallest Integer Divisible by K
    =====================================

    ============
    Description:
    ============

    Given a positive integer k, you need to find the length of the smallest
    positive integer n such that n is divisible by k, and n only contains the
    digit 1.

    Return the length of n. If there is no such n, return -1.

    =====
    Note: n may not fit in a 64-bit signed integer. 
    =====

    ===========================================
    FUNCTION: int smallestRepunitDivByK(int k);
    ===========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: k = 1
    Output: 1
    Explanation: The smallest answer is n = 1, which has length 1.

    --- Example 2 ---
    Input: k = 2
    Output: -1
    Explanation: There is no such positive integer n divisible by 2.

    --- Example 3 ---
    Input: k = 3
    Output: 3
    Explanation: The smallest answer is n = 111, which has length 3.


    *** Constraints ***
    1 <= k <= 10^5

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  52.58% */

/* Time  Complexity: O(K) */
/* Space Complexity: O(1) */
class Solution {
public:
    int smallestRepunitDivByK(int k)
    {
        int remainder = 0;

        for (int len_n = 1; len_n <= k; len_n++)
        {
            remainder = (remainder * 10 + 1) % k;

            if (remainder == 0)
                return len_n;
        }

        return -1;
    }
};
