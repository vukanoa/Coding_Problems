/*
    ============
    === HARD ===
    ============

    ===============================================
    689) Maximum Sum of 3 Non-Overlapping Subarrays
    ===============================================

    ============
    Description:
    ============

    Given an integer array nums and an integer k, find three non-overlapping
    subarrays of length k with maximum sum and return them.

    Return the result as a list of indices representing the starting position
    of each interval (0-indexed). If there are multiple answers, return the
    lexicographically smallest one.

    =======================================================================
    FUNCTION: vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k);
    =======================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,1,2,6,7,5,1], k = 2
    Output: [0,3,5]
    Explanation: Subarrays [1, 2], [2, 6], [7, 5] correspond to the starting indices [0, 3, 5].
    We could have also taken [2, 1], but an answer of [1, 3, 5] would be lexicographically larger.

    --- Example 2 ---
    Input: nums = [1,2,1,2,1,2,1,2,1], k = 2
    Output: [0,2,4]


    *** Constraints ***
    1 <= nums.length <= 2 * 10^4
    1 <= nums[i] < 2^16
    1 <= k <= floor(nums.length / 3)

*/

#include <climits>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO
    Classic Memoization problem.

*/

/* Time  Beats: 22.76% */
/* Space Beats: 20.60% */

/* Time  Complexity: O(n * M) ~ O(n) */
/* Space Complexity: O(n * M) ~ O(n) */
class Solution {
public:
    vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k)
    {
        // Number of possible subarray starting positions
        const int N = nums.size() - k + 1;

        // Calculate sum of all possible k-length subarrays
        vector<int> sums(N);

        int window_sum = 0;
        for (int i = 0; i < k; i++)
            window_sum += nums[i];

        sums[0] = window_sum;

        // Sliding window to calculate remaining sums
        for (unsigned long int i = k; i < nums.size(); i++)
        {
            window_sum = window_sum - nums[i - k] + nums[i];
            sums[i - k + 1] = window_sum;
        }

        // memo[i][j]: max sum possible starting from index i with j subarrays
        // remaining
        vector<vector<int>> memo(N, vector<int>(4, -1));
        vector<int> indices;

        // First find optimal sum using DP
        dp(sums, k, 0, 3, memo);

        // Then reconstruct the path to find indices
        dfs(sums, k, 0, 3, memo, indices);

        return indices;
    }

private:
    // DP function to find maximum possible sum
    int dp(vector<int>& sums, int k, int idx, int rem, vector<vector<int>>& memo)
    {
        if (rem == 0)
            return 0;

        if (idx >= sums.size())
            return rem > 0 ? INT_MIN : 0;

        if (memo[idx][rem] != -1)
            return memo[idx][rem];

        // Try taking current subarray vs skipping it
        int with_current = sums[idx] + dp(sums, k, idx + k, rem - 1, memo);
        int skip_current = dp(sums, k, idx + 1, rem, memo);

        memo[idx][rem] = max(with_current, skip_current);
        return memo[idx][rem];
    }

    // DFS to reconstruct the solution path
    void dfs(vector<int>& sums, int k, int idx, int rem, vector<vector<int>>& memo, vector<int>& indices)
    {
        if (rem == 0)
            return;

        if (idx >= sums.size())
            return;

        int with_current = sums[idx] + dp(sums, k, idx + k, rem - 1, memo);
        int skip_current = dp(sums, k, idx + 1, rem, memo);

        // Choose path that gave optimal result in DP
        if (with_current >= skip_current) // Take current subarray
        {
            indices.push_back(idx);
            dfs(sums, k, idx + k, rem - 1, memo, indices);
        }
        else // Skip current subarray
        {
            dfs(sums, k, idx + 1, rem, memo, indices);
        }
    }
};
