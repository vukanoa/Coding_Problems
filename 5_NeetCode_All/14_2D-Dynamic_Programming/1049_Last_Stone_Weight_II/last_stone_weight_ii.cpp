/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    1049) Last Stone Weight II
    ===========================

    ============
    Description:
    ============

    You are given an array of integers stones where stones[i] is the weight of
    the ith stone.

    We are playing a game with the stones. On each turn, we choose any two
    stones and smash them together. Suppose the stones have weights x and y
    with x <= y. The result of this smash is:

        If x == y, both stones are destroyed, and If x != y, the stone of
        weight x is destroyed, and the stone of weight y has new weight y - x.

    At the end of the game, there is at most one stone left.

    Return the smallest possible weight of the left stone. If there are no
    stones left, return 0.

    =====================================================
    FUNCTION: int lastStoneWeightII(vector<int>& stones);
    =====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: stones = [2,7,4,1,8,1]
    Output: 1
    Explanation:
    We can combine 2 and 4 to get 2, so the array converts to [2,7,1,8,1] then,
    we can combine 7 and 8 to get 1, so the array converts to [2,1,1,1] then,
    we can combine 2 and 1 to get 1, so the array converts to [1,1,1] then,
    we can combine 1 and 1 to get 0, so the array converts to [1], then that's
    the optimal value.


    --- Example 2 ---
    Input: stones = [31,26,33,21,40]
    Output: 5


    *** Constraints ***
    1 <= stones.length <= 30
    1 <= stones[i] <= 100

*/

#include <vector>
#include <numeric>
#include <bits/stdc++.h>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO (Knapsack 0-1)

*/

/* Time  Beats: 36.49% */
/* Space Beats: 71.82% */

/* Time  Complexity: O(N * sum) */
/* Space Complexity: O(N * sum) */
class Solution_Bottom_Up_DP {
public:
    int lastStoneWeightII(vector<int>& stones)
    {
        const int N = stones.size();
        int result = INT_MAX;

        int total_sum = accumulate(stones.begin(), stones.end(), 0);
        vector<vector<bool>> dp(N+1, vector(total_sum + 1, false));

        for (int i = 0; i < N+1; i++)
            dp[i][0] = true;

        for (int i = 1; i < N+1; i++)
        {
            for (int curr_sum = 1; curr_sum < total_sum+1; curr_sum++)
            {
                if (dp[i-1][curr_sum] || (curr_sum - stones[i-1] >= 0 && dp[i-1][curr_sum - stones[i-1]]))
                    dp[i][curr_sum] = true;
            }
        }

        for (int curr_sum = 0; curr_sum < total_sum+1; curr_sum++)
            result = min(result, dp[N][curr_sum] ? abs(total_sum - 2 * curr_sum) : INT_MAX);

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 11.52% */
/* Space Beats:  9.07% */

/* Time  Complexity: O(N * sum) */
/* Space Complexity: O(N * sum) */
class Solution_Top_Down__Memoization__Left_or_Right_Subset {
private:
    vector<vector<int>> memo;

public:
    int lastStoneWeightII(vector<int>& stones)
    {
        const int N = stones.size();

        int total_sum = accumulate(stones.begin(), stones.end(), 0);

        /* Initialize */
        memo = vector<vector<int>>(N, vector<int>(2 * total_sum + 1, -1));

        return solve(0, total_sum, total_sum, stones);
    }

private:
    int solve(int i, int target, int total_sum, const vector<int>& stones)
    {
        const int N = stones.size();

        if (i == N)
            return abs(target - total_sum);

        if (memo[i][target] != -1)
            return memo[i][target];

        int put_in_left_subset  = solve(i + 1, target - stones[i], total_sum, stones);
        int put_in_right_subset = solve(i + 1, target + stones[i], total_sum, stones);

        return memo[i][target] = min(put_in_left_subset,
                                     put_in_right_subset);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This is also a Memoization technique, howver this Solutions is conceptually
    different from the one above.

    It is beneficial to understand both.

*/

/* Time  Beats: 23.75% */
/* Space Beats: 31.40% */

/* Time  Complexity: O(N * sum) */
/* Space Complexity: O(N * sum) */
class Solution_Top_Down__Memoization__Skip_Take {
private:
    vector<vector<int>> memo;

public:
    int lastStoneWeightII(vector<int>& stones)
    {
        const int N = stones.size();

        int total_sum = accumulate(stones.begin(), stones.end(), 0);
        int target = total_sum / 2;

        /* Initialize */
        memo = vector<vector<int>>(N, vector<int>(target + 1, -1));

        int best = solve(0, target, stones);

        return total_sum - 2 * best;
    }

private:
    int solve(int i, int remaining, const vector<int>& stones)
    {
        const int N = stones.size();

        if (i == N || remaining == 0)
            return 0;

        if (memo[i][remaining] != -1)
            return memo[i][remaining];

        int skip = solve(i + 1, remaining, stones);

        int take = 0;
        if (stones[i] <= remaining)
            take = stones[i] + solve(i + 1, remaining - stones[i], stones);

        return memo[i][remaining] = max(skip, take);
    }
};
