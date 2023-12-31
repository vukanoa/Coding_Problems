#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    =============================================
    673) Number of Longest Increasing Subsequence
    =============================================

    ============
    Description:
    ============

    Given an integer array nums, return the number of longest increasing
    subsequences.

    Notice that the sequence has to be strictly increasing.

    =================================================
    FUNCTION: int findNumberOfLIS(vector<int>& nums);
    =================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,3,5,4,7]
    Output: 2
    Explanation: The two longest increasing subsequences are [1, 3, 4, 7] and
    [1, 3, 5, 7].


    --- Example 2 ---
    Input: nums = [2,2,2,2,2]
    Output: 5
    Explanation: The length of the longest increasing subsequence is 1, and
    there are 5 increasing subsequences of length 1, so output 5.


    *** Constraints ***
    1 <= nums.length <= 2000
    -10^6 <= nums[i] <= 10^6

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 41.01% */
/* Space Beats: 88.42% */

/* Time  Complexity: O(n^2) */
/* Space Complexity: O(n)   */
class Solution {
public:
    int findNumberOfLIS(vector<int>& nums)
    {
        const int n = nums.size();

        if (n == 1)
            return 1;

        std::vector<std::pair<int, int>> dp(n, std::pair<int, int>());
        dp[n-1].first  = 1;
        dp[n-1].second = 1;

        int max_longest_increasing = 0;

        for (int i = n-2; i >= 0; i--)
        {
            int longest_increasing = 1;
            bool flag = false;
            for (int j = i+1; j < n; j++)
            {
                if (nums[i] < nums[j])
                {
                    longest_increasing = std::max(longest_increasing, dp[j].first);
                    flag = true;
                }
            }

            int count = 0;
            for (int j = i+1; j < n; j++)
            {
                if (nums[i] < nums[j] && dp[j].first == longest_increasing)
                    count += dp[j].second;
            }

            dp[i].first  = longest_increasing;
            dp[i].first  += flag ? 1 : 0;
            dp[i].second = flag ? count : 1;

            max_longest_increasing = std::max(max_longest_increasing, dp[i].first);
        }

        int result = 0;
        for (int i = 0; i < n; i++)
        {
            if (dp[i].first == max_longest_increasing)
                result += dp[i].second;
        }

        return result;
    }
};
