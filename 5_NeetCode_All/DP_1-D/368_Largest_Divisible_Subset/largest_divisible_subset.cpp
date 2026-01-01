/*
    ==============
    === MEDIUM ===
    ==============

    =============================
    368) Largest Divisible Subset
    =============================

    ============
    Description:
    ============

    Given a set of distinct positive integers nums, return the largest subset
    answer such that every pair (answer[i], answer[j]) of elements in this
    subset satisfies:

        answer[i] % answer[j] == 0, or
        answer[j] % answer[i] == 0

    If there are multiple solutions, return any of them.

    ================================================================
    FUNCTION: vector<int> largestDivisibleSubset(vector<int>& nums);
    ================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,3]
    Output: [1,2]
    Explanation: [1,3] is also accepted.

    --- Example 2 ---
    Input: nums = [1,2,4,8]
    Output: [1,2,4,8]


    *** Constraints ***
    1 <= nums.length <= 1000
    1 <= nums[i] <= 2 * 10^9
    All the integers in nums are unique.

*/

#include <algorithm>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Similar DP to "Longest Increasing Subsequence" Problem.

*/

/* Time  Beats: 31.03% */
/* Space Beats: 73.14% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(N)   */
class Solution {
public:
    vector<int> largestDivisibleSubset(vector<int>& nums)
    {
        const int N = nums.size();
        vector<int> result;

        sort(nums.begin(), nums.end());

        vector<int>   dp(N, 1);
        vector<int> prev(N, -1);

        int end_idx_of_max_subset = 0;
        for (int i = 1; i < N; i++)
        {
            for (int j = 0; j < i; j++)
            {
                if (nums[i] % nums[j] == 0 && dp[i] < dp[j] + 1)
                {
                    dp[i]   = dp[j] + 1;
                    prev[i] = j;
                }
            }

            if (dp[i] > dp[end_idx_of_max_subset])
                end_idx_of_max_subset = i;
        }

        for (int i = end_idx_of_max_subset; i >= 0; i = prev[i])
        {
            result.push_back(nums[i]);

            if (prev[i] == -1)
                break;
        }

        return result;
    }
};
