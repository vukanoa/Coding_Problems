#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    377) Combination Sum IV
    ===========================

    ============
    Description:
    ============

    Given an array of distinct integers nums and a target integer target,
    return the number of possible combinations that add up to target.

    The test cases are generated so that the answer can fit in a 32-bit
    integer.

    =============================================================
    FUNCTION: int combinationSum4(vector<int>& nums, int target);
    =============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,3], target = 4
    Output: 7
    Explanation:
    The possible combination ways are:
    (1, 1, 1, 1)
    (1, 1, 2)
    (1, 2, 1)
    (1, 3)
    (2, 1, 1)
    (2, 2)
    (3, 1)
    Note that different sequences are counted as different combinations.


    *** Constraints ***
    Input: nums = [9], target = 3
    Output: 0

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  20.17% */

/* Time  Complexity: O(target * n) */
/* Space Complexity: O(target)     */
class Solution_Bottom-Up {
public:
    int combinationSum4(std::vector<int>& nums, int target)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates

        vector<unsigned int> dp(target + 1, 0);
        dp[0] = 1;

        for (int i = 1; i <= target; i++)
        {
            for (int num : nums)
            {
                if (i - num >= 0)
                    dp[i] += dp[i - num];
            }
        }

        return dp[target];
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:   5.97% */

/* Time  Complexity: O(target * n) */
/* Space Complexity: O(target)     */
class Solution_Memoization {
public:
    int combinationSum4(std::vector<int>& nums, int target)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates

        std::sort(nums.begin(), nums.end());

        // Memoization map for caching results
        std::unordered_map<int, int> memo;

        return helper(nums, target, memo);
    }

private:
    int helper(const std::vector<int>& nums, int target, std::unordered_map<int, int>& memo)
    {
        // Check if result is already computed
        if (memo.find(target) != memo.end())
            return memo[target];

        // Base cases
        if (target == 0)
            return 1;

        if (target < nums[0])
            return 0;

        int count = 0;

        // Recursively compute combination sums
        for (int num : nums)
        {
            if (target - num < 0)
                break;

            count += helper(nums, target - num, memo);
        }

        // Cache the result
        memo[target] = count;

        return count;
    }
};
