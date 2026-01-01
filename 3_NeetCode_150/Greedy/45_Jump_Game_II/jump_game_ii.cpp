#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    45) Jump Game II
    ===========================

    ============
    Description:
    ============

    You are given a 0-indexed array of integers nums of length n. You are
    initially positioned at nums[0].

    Each element nums[i] represents the maximum length of a forward jump from
    index i. In other words, if you are at nums[i], you can jump to any
    nums[i + j] where:

        0 <= j <= nums[i] and i + j < n

    Return the minimum number of jumps to reach nums[n - 1]. The test cases are
    generated such that you can reach nums[n - 1].

    ======================================
    FUNCTION: int jump(vector<int>& nums);
    ======================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [2,3,1,1,4]
    Output: 2
    Explanation: The minimum number of jumps to reach the last index is 2.
                 Jump 1 step from index 0 to 1, then 3 steps to the last index.


    --- Example 2 ---
    Input: nums = [2,3,0,1,4]
    Output: 2


    *** Constraints ***
    1 <= nums.length <= 104
    0 <= nums[i] <= 1000
    It's guaranteed that you can reach nums[n - 1].

*/

/*
    ------------
    --- IDEA ---
    ------------

    Classical "fibonacci" type of Dynamic Programming technique.

*/

/* Time  Beats:  8.07% */
/* Space Beats: 19.33% */

/* Time  Complexity: O(n * max(nums)) */
/* Space Complexity: O(n) */
class Solution {
public:
    int jump(std::vector<int>& nums)
    {
        int n = nums.size();

        std::vector<int> dp(n, INT_MAX);
        dp[n-1] = 0;

        for (int i = n-2; i >= 0; i--)
        {
            for (int j = 1; j <= nums[i]; j++)
            {
                if (i + j >= n)
                    break;

                if (dp[i + j] != INT_MAX)
                    dp[i] = std::min(dp[i], 1 + dp[i + j]);
            }
        }

        return dp[0];
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Something between Solution_DP and Solution_BFS in this file.
    A kind of combination of the two.

    Better than the first(Solution_DP) and worse than the last(Solution_BFS).

*/

/* Time  Beats: 32.55% */
/* Space Beats: 19.33% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    int jump(std::vector<int>& nums)
    {
        int n = nums.size();
        std::vector<int> dp(n, INT_MAX);

        dp[0] = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 1; j <= nums[i]; j++)
            {
                if (i + j >= n)
                    continue;

                if (dp[i + j] == INT_MAX) // If it's not yet level-marked
                    dp[i + j] = dp[i] + 1;

                if (i+j == n-1)
                    return dp[i + j];
            }
        }

        return 0;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    You can think of this as kind of a BFS in a way. It's actually Greedy, but
    the way we're "traversing" the vector is in a "BFS-like" way.

*/

/* Time  Beats: 95.10% */
/* Space Beats: 43.87% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    int jump(std::vector<int>& nums)
    {
        int n = nums.size();
        int jumps = 0;

        int left  = 0;
        int right = 0;

        while (right < n-1)
        {
            int farthest = 0;
            for (int j = left; j <= right; j++)
                farthest = std::max(farthest, j + nums[j]);

            left  = right + 1;
            right = farthest;

            jumps++;
        }

        return jumps;
    }
};
