#include <iostream>
#include <vector>
#include <numeric>
#include <cstring> // memset

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

/*
    ------------
    --- IDEA ---
    ------------

    TODO (Knapsack 0-1)

*/

/* Time  Beats: 36.49% */
/* Space Beats: 71.82% */

/* Time  Complexity: O(n * sum) */
/* Space Complexity: O(n * sum) */
class Solution_Bottom_Up_DP {
public:
    int lastStoneWeightII(vector<int>& stones)
    {
        const int N = stones.size();
        int min_difference = INT_MAX;

        int sum = std::accumulate(stones.begin(), stones.end(), 0);
        std::vector<std::vector<bool>> dp(N+1, std::vector(sum + 1, false));

        for (int i = 0; i < N+1; i++)
            dp[i][0] = true;

        for (int i = 1; i < N+1; i++)
        {
            for (int j = 1; j < sum+1; j++)
            {
                if (dp[i-1][j] || (j-stones[i-1] >= 0 &&  dp[i-1][j - stones[i-1]]) )
                    dp[i][j] = true;
            }
        }

        for (int j = 0; j < sum+1; j++)
            min_difference = std::min(min_difference, dp[N][j] ? std::abs(sum-2*j) : INT_MAX);

        return min_difference;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO (From Decision Tree(Backtracking) to DP using Memoization)

*/

/* Time  Beats:  7.47% */
/* Space Beats: 11.67% */

/* Time  Complexity: O(n * sum) */
/* Space Complexity: O(n * sum) */
class Solution_Memo_1 {
private: // This is implicit
    struct PairHash {
        std::size_t operator () (const std::pair<int, int>& p) const
        {
            auto h1 = std::hash<int>()(p.first);
            auto h2 = std::hash<int>()(p.second);

            return h2 ^ (h1 << 1);
        }
    };

public:
    int lastStoneWeightII(vector<int>& stones)
    {
        int sum = std::accumulate(stones.begin(), stones.end(), 0);
        int target = sum / 2; // Integer division

        std::unordered_map<std::pair<int, int>, int, PairHash> cache;

        /* Lambda */
        std::function<int(int, int)> dfs;
        dfs = [&](int i, int total) -> int
        {
            if (total >= target || i == stones.size())
                return std::abs(sum - 2*total);

            if (cache.find(std::make_pair(i, total)) != cache.end()) // Already computed
                return cache[std::make_pair(i, total)];

            cache[std::make_pair(i, total)] = std::min(dfs(i+1, total), dfs(i+1, total + stones[i]));

            return cache[std::make_pair(i, total)];
        };

        return dfs(0, 0);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO (Same IDEA as above, but written in a much more efficient way)

*/

/* Time  Beats: 100% */
/* Space Beats: 5089% */

/* Time  Complexity: O(n * sum) */
/* Space Complexity: O(n * sum) */
class Solution_Memo_2 {
public:
    int dp[30][6000];
    int lastStoneWeightII(vector<int>& stones)
    {
        memset(dp, -1, sizeof(dp));

        return dfs(0, 0, stones);
    }

private:

    int dfs(int i,int val,vector<int>&stones)
    {
        if(i == stones.size())
        {
            if(val < 0)
                return 1e9;

            return 0;
        }

        if(dp[i][val+3000] != -1)
            return dp[i][val+3000];

        int positive =  stones[i] + dfs(i+1, val+stones[i], stones);
        int negative = -stones[i] + dfs(i+1, val-stones[i], stones);

        return dp[i][val+3000] = min(positive, negative);
    }
};
