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

#include <climits>
#include <cstring>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Foundational "Bottom up, Tabulation Dynammic Programming" technique.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  61.06% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Bottom_Up__Tabulation {
public:
    int minCostClimbingStairs(vector<int>& cost)
    {
        const int N = cost.size();

        if (N == 2)
            return min(cost[0], cost[1]);

        vector<int> dp(N+1, INT_MAX);
        dp[0] = cost[0];
        dp[1] = cost[1];

        for (int i = 2; i <= N; i++)
        {
            dp[i] = min(dp[i-2], dp[i-1])  +  (i == N ? 0 : cost[i]);
        }

        return dp[N];
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same as above, however this one is more Space efficient since it doesn't
    use an entire "dp" vector, but only last two elements.

    Therefore Space Complexity reduces from O(N) to O(1), which can be huge
    depending on the magnitude of N.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  83.58% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Bottom_Up__Tabulation_Optimized {
public:
    int minCostClimbingStairs(vector<int>& cost)
    {
        const int N = cost.size();

        if (N == 2)
            return min(cost[0], cost[1]);

        int prev_prev = cost[0];
        int prev      = cost[1];

        for (int i = 2; i <= N; i++)
        {
            int curr = min(prev_prev, prev)  +  (i == N ? 0 : cost[i]);

            prev_prev = prev;
            prev      = curr;
        }

        return prev;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Classic Top-Down Memoization Solution.

*/

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Top_Down__Memoization_1 {
private:
    int memo[1002];

public:
    int minCostClimbingStairs(vector<int>& cost)
    {
        const int N = cost.size();

        if (N == 2)
            return min(cost[0], cost[1]);

        /* Memset */
        memset(memo, 0xff, sizeof(memo));

        return min(solve(0, cost),
                   solve(1, cost));
    }

private:
    int solve(int idx, vector<int>& cost)
    {
        const int N = cost.size();

        if (idx >= N)
            return 0;

        if (memo[idx] != -1)
            return memo[idx];

        int take_one = cost[idx] + solve(idx + 1, cost);
        int take_two = cost[idx] + solve(idx + 2, cost);

        return memo[idx] = min(take_one, take_two);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same as above, implemented in a different way. It really depends on how you
    think about it.

    It's always beneficial to see multiple implementations of Memoization
    Solutions.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  70.82% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Top_Down__Memoization_2 {
private:
    int memo[1002];

public:
    int minCostClimbingStairs(vector<int>& cost)
    {
        const int N = cost.size();

        if (N == 2)
            return min(cost[0], cost[1]);

        /* Memset */
        memset(memo, 0xff, sizeof(memo));

        return solve(N, cost);
    }

private:
    int solve(int idx, vector<int>& cost)
    {
        const int N = cost.size();

        if (idx == 0 || idx == 1)
            return cost[idx];

        if (memo[idx] != -1)
            return memo[idx];

        int curr_cost = idx == N ? 0 : cost[idx];

        int take_one = solve(idx - 1, cost) + curr_cost;
        int take_two = solve(idx - 2, cost) + curr_cost;

        return memo[idx] = min(take_one, take_two);
    }
};
