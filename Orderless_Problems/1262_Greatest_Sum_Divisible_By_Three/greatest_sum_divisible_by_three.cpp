/*
    ==============
    === MEDIUM ===
    ==============

    =====================================
    1262) Greatest Sum Divisible by Three
    =====================================

    ============
    Description:
    ============

    Given an integer array nums, return the maximum possible sum of elements of
    the array such that it is divisible by three.

    ================================================
    FUNCTION: int maxSumDivThree(vector<int>& nums);
    ================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [3,6,5,1,8]
    Output: 18
    Explanation: Pick numbers 3, 6, 1 and 8 their sum is 18 (maximum sum
                 divisible by 3).

    --- Example 2 ---
    Input: nums = [4]
    Output: 0
    Explanation: Since 4 is not divisible by 3, do not pick any number.

    --- Example 3 ---
    Input: nums = [1,2,3,4,4]
    Output: 12
    Explanation: Pick numbers 1, 3, 4 and 4 their sum is 12 (maximum sum
                 divisible by 3).

    *** Constraints ***
    1 <= nums.length <= 4 * 10^4
    1 <= nums[i] <= 10^4

*/

#include <climits>
#include <cstring>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Classic Memoization, though maybe not obvious at first glance because it
    does NOT have a small Constraints.

    However, since "three" is hardcoded in the Description of a problem, the
    state can be O(N), thus making this Memoization technique feasible and
    optimal.

*/

/* Time  Beats: 74.56% */
/* Space Beats: 58.51% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Memoization {
private:
    int memo[40000][3];

public:
    int maxSumDivThree(vector<int>& nums)
    {
        const int N = nums.size();

        memset(memo, -1, sizeof(memo));

        return max(0, solve(N-1, 0, nums));
    }

private:
    int solve(int i, int target_mod, vector<int>& nums)
    {
        if (i < 0)
            return target_mod == 0 ? 0 : -1e9;

        if (memo[i][target_mod] != -1)
            return memo[i][target_mod];

        const int num     = nums[i];
        const int num_mod = num % 3;

        // We want the previous sum modulo 3 such that:
        // (prev_mod + x_mod) % 3 == target_mod
        const int prev_mod = (target_mod - num_mod + 3) % 3;

        const int take = num + solve(i - 1, prev_mod,   nums);
        const int skip =  0  + solve(i - 1, target_mod, nums);

        return memo[i][target_mod] = max(take, skip);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Iterative, Bottom-Up, way of implementing it. Memoization is usually eaiser
    to write, but Bottom-Up is usually preffereable since it doesn't have the
    overhead of the Call-Stack.

*/

/* Time  Beats: 38.95% */
/* Space Beats: 33.55% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Bottom_Up {
public:
    int maxSumDivThree(vector<int>& nums)
    {
        const int N = nums.size();

        // dp[i][m] = best sum with first i elements and modulo m
        vector<vector<int>> dp(N + 1, vector<int>(3, INT_MIN));
        dp[0][0] = 0; // Base case: zero elements, i.e. sum = 0 which has mod 0

        for (int i = 1; i <= N; i++)
        {
            int num     = nums[i - 1];
            int num_mod = num % 3;

            for (int curr_mod = 0; curr_mod < 3; curr_mod++)
            {
                // Skip
                int skip = dp[i - 1][curr_mod];

                // Take
                // previous_mod + x_mod == curr_mod (mod 3)
                int prev_mod = (curr_mod - num_mod + 3) % 3;
                int take = dp[i - 1][prev_mod] + num;

                dp[i][curr_mod] = max(skip, take);
            }
        }

        return max(0, dp[N][0]);
    }
};
