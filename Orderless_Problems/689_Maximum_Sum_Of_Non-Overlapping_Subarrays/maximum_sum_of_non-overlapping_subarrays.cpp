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
class Solution_Memoization {
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




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 52.57% */
/* Space Beats: 30.35% */

/* Time  Complexity: O(n * M) ~ O(n) */
/* Space Complexity: O(n * M) ~ O(n) */
class Solution_Tabulation {
public:
    vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k)
    {
        const int N = nums.size();

        // Prefix sum array to calculate sum of any subarray in O(1) time
        vector<int> prefix_sum(N + 1, 0);
        for (int i = 1; i <= N; i++)
            prefix_sum[i] = prefix_sum[i - 1] + nums[i - 1];

        // Arrays to store the best sum and starting indices for up to 3
        // subarrays
        vector<vector<int>> best_sum(4, vector<int>(N + 1, 0));
        vector<vector<int>> best_idx(4, vector<int>(N + 1, 0));

        // Compute the best sum and indices for 1, 2, and 3 subarrays
        for (int subarray_count = 1; subarray_count <= 3; subarray_count++)
        {
            for (int end_idx = k * subarray_count; end_idx <= N; end_idx++)
            {
                int curr_sum = prefix_sum[end_idx] - prefix_sum[end_idx - k] + best_sum[subarray_count - 1][end_idx - k];

                // Check if the current configuration gives a better sum
                if (curr_sum > best_sum[subarray_count][end_idx - 1])
                {
                    best_sum[subarray_count][end_idx] = curr_sum;
                    best_idx[subarray_count][end_idx] = end_idx - k;
                }
                else
                {
                    best_sum[subarray_count][end_idx] = best_sum[subarray_count][end_idx - 1];
                    best_idx[subarray_count][end_idx] = best_idx[subarray_count][end_idx - 1];
                }
            }
        }

        // Trace back the indices of the three subarrays
        vector<int> result(3, 0);
        int curr_end = N;
        for (int subarray_idx = 3; subarray_idx >= 1; subarray_idx--)
        {
            result[subarray_idx - 1] = best_idx[subarray_idx][curr_end];
            curr_end = result[subarray_idx - 1];
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  61.79% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Three_Pointers {
public:
    vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k)
    {
        const int N = nums.size();
        int max_sum = 0;

        // Prefix sum array to calculate sum of any subarray
        vector<int> prefix_sum(N + 1);
        for (int i = 0; i < N; i++)
            prefix_sum[i + 1] = prefix_sum[i] + nums[i];

        // Arrays to store the best starting index for the left and right
        // subarrays
        vector<int> left_max_idx(N);
        vector<int> right_max_idx(N);

        // Result array to store the starting indices of the three subarrays
        vector<int> result(3);

        // Calculate the best starting index for the left subarray for each
        // position
        for (int i = k, curr_max_sum = prefix_sum[k] - prefix_sum[0]; i < N; i++)
        {
            if (prefix_sum[i + 1] - prefix_sum[i + 1 - k] > curr_max_sum)
            {
                left_max_idx[i] = i + 1 - k;
                curr_max_sum = prefix_sum[i + 1] - prefix_sum[i + 1 - k];
            }
            else
            {
                left_max_idx[i] = left_max_idx[i - 1];
            }
        }

        // Calculate the best starting index for the right subarray for each
        // position
        right_max_idx[N - k] = N - k;
        for (int i = N - k - 1, curr_max_sum = prefix_sum[N] - prefix_sum[N - k]; i >= 0; i--)
        {
            if (prefix_sum[i + k] - prefix_sum[i] >= curr_max_sum)
            {
                right_max_idx[i] = i;
                curr_max_sum = prefix_sum[i + k] - prefix_sum[i];
            }
            else
            {
                right_max_idx[i] = right_max_idx[i + 1];
            }
        }

        // Iterate over the middle subarray and calculate the total sum for all
        // valid combinations
        for (int i = k; i <= N - 2 * k; i++)
        {
            int left_idx  = left_max_idx[i - 1];
            int right_idx = right_max_idx[i + k];

            int total_sum = (prefix_sum[i + k] - prefix_sum[i]) +
                            (prefix_sum[left_idx + k] - prefix_sum[left_idx]) +
                            (prefix_sum[right_idx + k] - prefix_sum[right_idx]);

            if (total_sum > max_sum)
            {
                max_sum = total_sum;

                result[0] = left_idx;
                result[1] = i;
                result[2] = right_idx;
            }
        }

        return result;
    }
};
