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

/* Time  Complexity: O(N * abs(target)) */
/* Space Complexity: O(N * abs(target)) */
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
