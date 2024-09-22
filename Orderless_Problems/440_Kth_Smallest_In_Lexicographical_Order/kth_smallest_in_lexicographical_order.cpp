#include <iostream>

/*
    ============
    === HARD ===
    ============

    ==========================================
    440) Kth Smallest in Lexicographical Order
    ==========================================

    ============
    Description:
    ============

    Given two integers n and k, return the kth lexicographically smallest
    integer in the range [1, n].

    ==========================================
    FUNCTION: int findKthNumber(int n, int k);
    ==========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 13, k = 2
    Output: 10
    Explanation: The lexicographical order is [1, 10, 11, 12, 13, 2, 3, 4, 5,
                 6, 7, 8, 9], so the second smallest number is 10.

    --- Example 2 ---
    Input: n = 1, k = 1
    Output: 1


    *** Constraints ***
    1 <= k <= n <= 10^9

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:   9.96% */

/* Time  Complexity: O(logn * logn) */
/* Space Complexity: O(1)           */
class Solution {
public:
    int findKthNumber(long n, int k)
    {
        long num = 1;
        for (int i = 1; i < k; )
        {
            int req = getReqNum(num, num+1, n);

            if (i+req <= k)
            {
                i += req;
                num++;
            }
            else
            {
                i++;
                num *= 10;
            }
        }

        return num;
    }

private:
    int getReqNum(long a, long b, long &n)
    {
        int gap = 0;

        while (a <= n)
        {
            gap += min(n+1,b)-a;
            a *= 10;
            b *= 10;
        }

        return gap;
    }
};
