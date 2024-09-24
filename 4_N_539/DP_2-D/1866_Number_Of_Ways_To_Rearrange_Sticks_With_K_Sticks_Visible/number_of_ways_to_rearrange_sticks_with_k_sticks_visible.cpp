#include <iostream>

/*
    ============
    === HARD ===
    ============

    ==============================================================
    1866) Number of Ways to Rearrange Sticks With K Sticks Visible
    ==============================================================

    ============
    Description:
    ============

    There are n uniquely-sized sticks whose lengths are integers from 1 to n.
    You want to arrange the sticks such that exactly k sticks are visible from
    the left. A stick is visible from the left if there are no longer sticks to
    the left of it.

        For example, if the sticks are arranged [1,3,2,5,4], then the sticks
        with lengths 1, 3, and 5 are visible from the left.

    Given n and k, return the number of such arrangements. Since the answer may
    be large, return it modulo 109 + 7.

    ============================================
    FUNCTION: int rearrangeSticks(int n, int k);
    ============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 3, k = 2
    Output: 3
    Explanation: [1,3,2], [2,3,1], and [2,1,3] are the only arrangements such
    that exactly 2 sticks are visible.  The visible sticks are underlined.

    --- Example 2 ---
    Input: n = 20, k = 11
    Output: 647427950
    Explanation: There are 647427950 (mod 109 + 7) ways to rearrange the sticks
                 such that exactly 11 sticks are visible.


    *** Constraints ***
    1 <= n <= 1000
    1 <= k <= n

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 89.09% */
/* Space Beats: 90.55% */

/* Time  Complexity: O(n * k) */
/* Space Complexity: O(n * k) */
class Solution {
    int mod = 1e9 + 7;
    int dp[1001][1001];

public:
    int rearrangeSticks(int n, int k)
    {
        memset(dp, -1, sizeof(dp));

        return dfs(n, k);
    }

private:
    long long dfs(int n, int k)
    {
        if (k == 0 || k > n)
            return 0;

        if (n <= 2)
            return 1;

        if (dp[n][k] != -1)
            return dp[n][k];

        long long result = 0;

        result = (result +   1   * dfs(n-1, k-1)) % mod; // along longest stick at rightmost position
        result = (result + (n-1) * dfs(n-1, k  )) % mod; // non-talong longest stick at rightmost position

        return dp[n][k] = result;
    }
};
