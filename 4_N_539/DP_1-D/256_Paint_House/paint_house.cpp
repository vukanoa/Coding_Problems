#include <iostream>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    256) Paint House
    ===========================

    ============
    Description:
    ============

    There is a row of n houses, where each house can be painted one of three
    colors: red, blue or green. The cost of painting each house with a certain
    color is different. You have to paint all the houses such that no two
    adjacent houses have the same color.

    The cost of painting each house with a certain color is represented by an
    nx3 cost matrix "costs".

        - For example: costs[0][0] is the cost of painting house 0 with the
          color red; costs[1][2] is the cost of painting house 1 with color
          green, and so on...

    Return the minimum cost to paint all the houses.

    ============================================================
    FUNCTION: int minCost(std::vector<std::vector<int>>& costs);
    ============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: costs = [[17, 2, 17], [16, 16, 5], [14, 3, 19]]
    Output: 10
    Explanation: Paint house 0 into blue, paint house 1 into green, paint
    house 2 into blue.
    Minimum cost: 2 + 5 + 3 = 10.

*/

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    int minCost(std::vector<std::vector<int>>& costs)
    {
        std::vector<int> dp = {0, 0, 0};

        for (int i = 0; i < costs.size(); i++)
        {
            int dp0 = costs[i][0] + std::min(dp[1], dp[2]);
            int dp1 = costs[i][1] + std::min(dp[0], dp[2]);
            int dp2 = costs[i][2] + std::min(dp[0], dp[1]);

            dp = {dp0, dp1, dp2};
        }

        return *std::min_element(dp.begin(), dp.end());;
    }
};
