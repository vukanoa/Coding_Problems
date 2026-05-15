/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    494) Target Sum
    ===========================

    ============
    Description:
    ============

    You are given an integer array nums and an integer target.

    You want to build an expression out of nums by adding one of the symbols
    '+' and '-' before each integer in nums and then concatenate all the
    integers.

        For example, if nums = [2, 1], you can add a '+' before 2 and a '-'
        before 1 and concatenate them to build the expression "+2-1".

    Return the number of different expressions that you can build, which
    evaluates to target.

    ===============================================================
    FUNCTION: int findTargetSumWays(vector<int>& nums, int target);
    ===============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,1,1,1,1], target = 3
    Output: 5
    Explanation: There are 5 ways to assign symbols to make the sum of nums be
                 target 3.

    -1 + 1 + 1 + 1 + 1 = 3
    +1 - 1 + 1 + 1 + 1 = 3
    +1 + 1 - 1 + 1 + 1 = 3
    +1 + 1 + 1 - 1 + 1 = 3
    +1 + 1 + 1 + 1 - 1 = 3



    --- Example 2 ---
    Input: nums = [1], target = 1
    Output: 1



    *** Constraints ***
    1 <= nums.length <= 20
    0 <= nums[i] <= 1000
    0 <= sum(nums[i]) <= 1000
    -1000 <= target <= 1000

*/

#include <cstring>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Classic Top-Down Memoization Solution.

*/

/* Time  Beats: 59.99% */
/* Space Beats: 73.56% */

/* Time  Complexity: O(N * sum(target)) */
/* Space Complexity: O(N * sum(target)) */
class Solution_Top_Down__Memoization {
private:
    int memo[21][4001];

public:
    int findTargetSumWays(vector<int>& nums, int target)
    {
        const int N = nums.size();

        /* Memset */
        memset(memo, 0xff, sizeof(memo));

        /* Solve */
        return solve(0, target, nums);
    }

private:
    int solve(int idx, int target, vector<int>& nums)
    {
        const int N = nums.size();

        if (idx == N)
            return target == 0 ? 1 : 0;

        if (memo[idx][target + 2000] != -1)
            return memo[idx][target + 2000];

        int take_positive = solve(idx + 1, target - nums[idx], nums);
        int take_negative = solve(idx + 1, target + nums[idx], nums);

        return memo[idx][target + 2000] = take_positive + take_negative;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This is one of those problems where Top-Down Memoization is a MUCH more
    natural way of solving this problem.

    However, you should ALWAYS do both(as it's ALWAYS possible) to further
    hone in on your "DP" skills.

*/

/* Time  Beats: 38.71% */
/* Space Beats:  7.82% */

/* Time  Complexity: O(N * sum(target)) */
/* Space Complexity: O(N * sum(target)) */
class Solution_Bottom_Up__Tabulation {
public:
    int findTargetSumWays(vector<int>& nums, int target)
    {
        const int N = nums.size();
        vector<vector<int>> dp(N+1, vector<int>(4001, 0));
        dp[N][0 + 2000] = 1;

        for (int i = N-1; i >= 0; i--)
        {
            for (int j = nums[i]; j < 4001; j++)
                dp[i][j] += dp[i+1][j - nums[i]];

            for (int j = (4001 - 1) - nums[i]; j >= 0; j--)
                dp[i][j] += dp[i+1][j + nums[i]];
        }

        return dp[0][target + 2000];
    }
};
