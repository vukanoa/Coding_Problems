#include <iostream>
#include <vector>

/*
    ============
    === HARD ===
    ============

    ===========================
    879) Profitable Schemes
    ===========================

    ============
    Description:
    ============

    There is a group of n members, and a list of various crimes they could
    commit. The ith crime generates a profit[i] and requires group[i] members
    to participate in it. If a member participates in one crime, that member
    can't participate in another crime.

    Let's call a profitable scheme any subset of these crimes that generates at
    least minProfit profit, and the total number of members participating in
    that subset of crimes is at most n.

    Return the number of schemes that can be chosen. Since the answer may be
    very large, return it modulo 109 + 7.

    ===============================================================================================
    FUNCTION: int profitableSchemes(int n, int minProfit, vector<int>& group, vector<int>& profit);
    ===============================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 5, minProfit = 3, group = [2,2], profit = [2,3]
    Output: 2
    Explanation: To make a profit of at least 3, the group could either commit
                 crimes 0 and 1, or just crime 1.  In total, there are 2
                 schemes.

    --- Example 2 ---
    Input: n = 10, minProfit = 5, group = [2,3,5], profit = [6,7,8]
    Output: 7
    Explanation: To make a profit of at least 5, the group could commit any
                 crimes, as long as they commit one.  There are 7 possible
                 schemes: (0), (1), (2), (0,1), (0,2), (1,2), and (0,1,2).

    *** Constraints ***
    1 <= n <= 100
    0 <= minProfit <= 100
    1 <= group.length <= 100
    1 <= group[i] <= 100
    profit.length == group.length
    0 <= profit[i] <= 100

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 91.17% */
/* Space Beats: 89.53% */

/* Time  Complexity: O(n * minProfit * group.size()) */
/* Space Complexity: O(n * minProfit)                */
class Solution {
public:
    static constexpr int MOD = 1'000'000'007;

    int profitableSchemes(int n, int minProfit, vector<int>& group, vector<int>& profit)
    {
        vector<vector<int>> dp(n+1, vector<int>(minProfit+1));

        auto new_dp = dp;
        for (int i = 0; i <= n; i++)
            dp[i][0] = 1;

        for (int i = (int)group.size()-1; i >= 0; i--)
        {
            for (int j = 0; j<=n; j++)
            {
                for (int p = 0; p <= minProfit; p++)
                {
                    int not_taken = dp[j][p];
                    int taken = 0;

                    if(group[i] <= j)
                        taken = dp[j - group[i]][max(0, p - profit[i])];

                    new_dp[j][p] = (taken + not_taken) % MOD;
                }
            }

            swap(dp, new_dp);
        }

        return dp[n][minProfit];
    }
};
