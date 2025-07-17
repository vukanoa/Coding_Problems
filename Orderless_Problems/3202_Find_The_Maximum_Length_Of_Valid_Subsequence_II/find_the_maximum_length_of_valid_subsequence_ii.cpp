/*
    ==============
    === MEDIUM ===
    ==============

    =====================================================
    3202) Find the Maximum Length of Valid Subsequence II
    =====================================================

    ============
    Description:
    ============

    You are given an integer array nums and a positive integer k.

    A subsequence sub of nums with length x is called valid if it satisfies:

        (sub[0] + sub[1]) % k == (sub[1] + sub[2]) % k == ... == (sub[x - 2] + sub[x - 1]) % k.

    Return the length of the longest valid subsequence of nums. 

    ======================================================
    FUNCTION: int maximumLength(vector<int>& nums, int k);
    ======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,3,4,5], k = 2
    Output: 5
    Explanation:
    The longest valid subsequence is [1, 2, 3, 4, 5].

    --- Example 2 ---
    Input: nums = [1,4,2,3,1,4], k = 3
    Output: 4
    Explanation:
    The longest valid subsequence is [1, 4, 1, 4].


    *** Constraints ***
    2 <= nums.length <= 10^3
    1 <= nums[i] <= 10^7
    1 <= k <= 10^3

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Pretty standard DP problem.

*/

/* Time  Beats: 89.68% */
/* Space Beats: 36.28% */

/* Time  Complexity: O(k^2 + N * K) */
/* Space Complexity: O(k^2)         */
class Solution {
public:
    int maximumLength(vector<int>& nums, int k)
    {
        vector<vector<int>> dp(k, vector<int>(k, 0));

        int result = 0;
        for (int& num : nums)
        {
            num %= k;
            for (int prev = 0; prev < k; prev++)
            {
                dp[prev][num] = dp[num][prev] + 1;

                result = max(result, dp[prev][num]);
            }
        }

        return result;
    }
};
