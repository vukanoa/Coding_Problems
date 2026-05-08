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

#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Similar to coin-change.

*/

/* Time  Beats: 37.16% */
/* Space Beats: 18.15% */

/* Time  Complexity: O(N * target) */
/* Space Complexity: O(N)          */
class Solution_Bottom_Up__Tabulation {
public:
    int combinationSum4(vector<int>& nums, int target)
    {
        const int N = nums.size();

        vector<unsigned> dp(target+1, 0);
        dp[0] = 1;

        /* Sort */
        sort(nums.begin(), nums.end());

        for (int curr_target = 0; curr_target <= target; curr_target++)
        {
            for (const int& num : nums)
            {
                if (curr_target - num < 0)
                    break;

                dp[curr_target] += dp[curr_target - num];
            }
        }

        return dp[target];
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same as above, but implemented in a Top-Down fashion, using Memoization.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  99.27% */

/* Time  Complexity: O(N * target) */
/* Space Complexity: O(N)          */
class Solution_Top_Down__Memoization {
private:
    int memo[1001];

public:
    int combinationSum4(vector<int>& nums, int target)
    {
        const int N = nums.size();

        /* Sort */
        sort(nums.begin(), nums.end());

        /* Memset */
        memset(memo, 0xff, sizeof(memo));

        return solve(target, nums);
    }

private:
    int solve(int target, vector<int>& nums)
    {
        if (target == 0)
            return 1;

        if (memo[target] != -1)
            return memo[target];

        int result = 0;
        for (const int& num : nums)
        {
            if (target - num < 0)
                break;

            result += solve(target - num, nums);
        }

        return memo[target] = result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Both this and the Solution above are correct implementationt of a
    Memoization technique, however this one is more GENERAL and thus LESS
    efficient.

    This one does NOT prune early, but makes one more recursion call.

    However, if you're getting into learning about Memoization it's always
    beneficial to see multiple different implementations of it.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  91.42% */

/* Time  Complexity: O(N * target) */
/* Space Complexity: O(N)          */
class Solution_Top_Down__General_Memoization {
private:
    int memo[1001];

public:
    int combinationSum4(vector<int>& nums, int target)
    {
        const int N = nums.size();

        /* Sort */
        sort(nums.begin(), nums.end());

        /* Memset */
        memset(memo, 0xff, sizeof(memo));

        return solve(target, nums);
    }

private:
    int solve(int target, vector<int>& nums)
    {
        if (target == 0)
            return 1;

        if (target < 0)
            return 0;

        if (memo[target] != -1)
            return memo[target];

        int result = 0;
        for (const int& num : nums)
            result += solve(target - num, nums);

        return memo[target] = result;
    }
};
