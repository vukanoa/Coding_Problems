#include <iostream>
#include <vector>

/*
    ============
    === EASY ===
    ============

    =============================
    746) Min Cost Climbing Stairs
    =============================

    ============
    Description:
    ============

    You are given an integer array cost where cost[i] is the cost of ith step
    on a staircase. Once you pay the cost, you can either climb one or two
    steps.

    You can either start from the step with index 0, or the step with index 1.

    Return the minimum cost to reach the top of the floor.

    =======================================================
    FUNCTION: int minCostClimbingStairs(vector<int>& cost);
    =======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: cost = [10,15,20]
    Output: 15
    Explanation: You will start at index 1.
    - Pay 15 and climb two steps to reach the top.
    The total cost is 15.

    --- Example 2 ---
    Input: cost = [1,100,1,1,1,100,1,1,100,1]
    Output: 6
    Explanation: You will start at index 0.
    - Pay 1 and climb two steps to reach index 2.
    - Pay 1 and climb two steps to reach index 4.
    - Pay 1 and climb two steps to reach index 6.
    - Pay 1 and climb one step to reach index 7.
    - Pay 1 and climb two steps to reach index 9.
    - Pay 1 and climb one step to reach the top.
    The total cost is 6.


    *** Constraints ***
    2 <= cost.length <= 1000
    0 <= cost[i] <= 999

*/

/*
    ------------
    --- IDEA ---
    ------------

    Typical, foundational "Bottom up Dynammic Programming" technique.

*/


/* Time  Beats: 100.00% */
/* Space Beats:  61.06% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost)
    {
        const int n = cost.size();
        std::vector<int> dp(n, 0);

        dp[0] = cost[0];
        dp[1] = cost[1];

        for (int i = 2; i < n; i++)
            dp[i] = cost[i] + std::min(dp[i-2], dp[i-1]);

        return std::min(dp[n-2], dp[n-1]);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same as above, however this one is more Space efficient since it doesn't
    use an entire vector, but only last two elements in every iteration.

    Therefore Space Complexity comes down from O(n) to O(1), which can be huge
    depending on the size of n.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  83.58% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Efficient {
public:
    int minCostClimbingStairs(vector<int>& cost)
    {
        const int n = cost.size();

        int dp_2 = cost[0];
        int dp_1 = cost[1];

        for (int i = 2; i < n; i++)
        {
            int curr = cost[i] + std::min(dp_2, dp_1);

            dp_2 = dp_1;
            dp_1 = curr;
        }

        return std::min(dp_2, dp_1);
    }
};
