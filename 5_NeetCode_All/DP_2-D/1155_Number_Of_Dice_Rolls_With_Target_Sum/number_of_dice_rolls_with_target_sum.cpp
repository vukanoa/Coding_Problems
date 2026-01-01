#include <iostream>

/*
    ==============
    === MEDIUM ===
    ==============

    ==========================================
    1155) Number of Dice Rolls With Target Sum
    ==========================================

    ============
    Description:
    ============

    You have n dice, and each dice has k faces numbered from 1 to k.

    Given three integers n, k, and target, return the number of possible ways
    (out of the kn total ways) to roll the dice, so the sum of the face-up
    numbers equals target. Since the answer may be too large, return it modulo
    10^9 + 7.

    =========================================================
    FUNCTION: int numRollsToTarget(int n, int k, int target);
    =========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 1, k = 6, target = 3
    Output: 1
    Explanation: You throw one die with 6 faces.
    There is only one way to get a sum of 3.


    --- Example 2 ---
    Input: n = 2, k = 6, target = 7
    Output: 6
    Explanation: You throw two dice, each with 6 faces.
    There are 6 ways to get a sum of 7: 1+6, 2+5, 3+4, 4+3, 5+2, 6+1.


    --- Example 3 ---
    Input: n = 30, k = 30, target = 500
    Output: 222616187
    Explanation: The answer must be returned modulo 109 + 7.


    *** Constraints ***
    1 <= n, k <= 30
    1 <= target <= 1000

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 91.42% */
/* Space Beats: 90.82% */

/* Time  Complexity: O(target * n * k) */
/* Space Complexity: O(n * target)     */
class Solution {
public:
    int dp[31][1001];
    const long long mod = 1e9 + 7;

    int n;
    int k;
    int numRollsToTarget(int n, int k, int target)
    {
        this->n = n;
        this->k = k;

        fill(&dp[0][0], &dp[0][0] + 31*1001, -1);

        return dfs(n, target);
    }

private:
    int dfs(int i, int t)
    {
        if (i == 0 && t == 0)
            return 1; // Base case

        if (i <= 0 || t <= 0)
            return 0;

        if (dp[i][t] != -1)
            return dp[i][t];

        long long result = 0;

        for (int p = 1; p <= k; p++)
            result = (result + dfs(i-1, t-p)) % mod;

        return dp[i][t] = result;
    }
};
