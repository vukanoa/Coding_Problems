#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ====================================
    1027) Longest Arithmetic Subsequence
    ====================================

    ============
    Description:
    ============


    Given an array nums of integers, return the length of the longest arithmetic subsequence in nums.

    Note that:

        + A subsequence is an array that can be derived from another array by
          deleting some or no elements without changing the order of the
          remaining elements.

        + A sequence seq is arithmetic if seq[i + 1] - seq[i] are all the same
          value (for 0 <= i < seq.length - 1).

    =======================================================
    FUNCTION: int longestArithSeqLength(vector<int>& nums);
    =======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [3,6,9,12]
    Output: 4
    Explanation:  The whole array is an arithmetic sequence with steps of
                  length = 3.

    --- Example 2 ---
    Input: nums = [9,4,7,2,10]
    Output: 3
    Explanation:  The longest arithmetic subsequence is [4,7,10].

    --- Example 3 ---
    Input: nums = [20,1,15,3,10,5,8]
    Output: 4
    Explanation:  The longest arithmetic subsequence is [20,15,10,5].


    *** Constraints ***
    2 <= nums.length <= 1000
    0 <= nums[i] <= 500

*/

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 72,93% */
/* Space Beats: 19.67% */

/* Time  Complexity: O(n^2) */
/* Space Complexity: O(M) */ // Where M == (max_elem(nums) + max_elem(nums)) - (min_elem(nums) - min_elem(nums))
class Solution {
public:
    int longestArithSeqLength(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 2;

        vector<vector<int>> dp(N, vector<int>(2000, 0));
        for (int i = 0; i < N; i++)
        {
            for (int j = i+1; j < N; j++)
            {
                int diff = nums[j] - nums[i] + 1000; // +1000 for indexing

                dp[j][diff] = max(2, dp[i][diff] + 1);
                result = max(result, dp[j][diff]);
            }
        }

        return result;
    }
};
