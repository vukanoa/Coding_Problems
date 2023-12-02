#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    343) Integer Break
    ===========================

    ============
    Description:
    ============

    Given an integer n, break it into the sum of k positive integers, where k
    >= 2, and maximize the product of those integers.

    Return the maximum product you can get.

    ==================================
    FUNCTION: int integerBreak(int n);
    ==================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 2
    Output: 1
    Explanation: 2 = 1 + 1, 1 × 1 = 1.


    --- Example 2 ---
    Input: n = 10
    Output: 36
    Explanation: 10 = 3 + 3 + 4, 3 × 3 × 4 = 36.


    *** Constraints ***
    2 <= n <= 58

*/

/* Time  Beats:   100% */
/* Space Beats: 19.60% */

/* Time  Complexity: O(n^2) */
/* Space Complexity: O(n)   */
class Solution_Memoization {
public:
    int integerBreak(int n)
    {
        std::vector<int> dp(n+1, 0);
        dp[1] = 1;

        std::function<int(int)> dfs;
        dfs = [&](int num) -> int
        {
            if (dp[num] != 0)
                return dp[num];

            dp[num] = (num == n) ? 0 : num;

            for (int i = 1; i < num; i++)
            {
                int val = dfs(i) * dfs(num - i);
                dp[num] = std::max(dp[num], val);
            }

            return dp[num];
        };

        return dfs(n);
    }
};




/* Time  Beats: 100%   */
/* Space Beats: 38.19% */

/* Time  Complexity: O(n^2) */
/* Space Complexity: O(n)   */
class Solution_Bottom_Up {
public:
    int integerBreak(int n)
    {
        std::vector<int> dp(n+1, 0);
        dp[1] = 1;

        for (int num = 2; num <= n; num++)
        {
            dp[num] = (num == n) ? 0 : num;

            for (int i = 1; i < num; i++)
            {
                int val = dp[i] * dp[num - i];
                dp[num] = std::max(dp[num], val);
            }
        }

        return dp[n];
    }
};
