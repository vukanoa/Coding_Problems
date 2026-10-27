/*
    ============
    === HARD ===
    ============

    ============================
    3748) Count Stable Subarrays
    ============================

    ============
    Description:
    ============


    You are given an integer array nums.

    A subarray of nums is called stable if it contains no inversions, i.e.,
    there is no pair of indices i < j such that nums[i] > nums[j].

    You are also given a 2D integer array queries of length q, where each
    queries[i] = [li, ri] represents a query. For each query [li, ri], compute
    the number of stable subarrays that lie entirely within the segment
    nums[li..ri].

    Return an integer array ans of length q, where ans[i] is the answer to the
    ith query.

    =====
    Note: A single element subarray is considered stable. 
    =====

    ==================================================================================================
    FUNCTION: vector<long long> countStableSubarrays(vector<int>& nums, vector<vector<int>>& queries);
    ==================================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [3,1,2], queries = [[0,1],[1,2],[0,2]]
    Output: [2,3,4]
    Explanation:
        For queries[0] = [0, 1], the subarray is [nums[0], nums[1]] = [3, 1].
            The stable subarrays are [3] and [1]. The total number of stable subarrays is 2.
        For queries[1] = [1, 2], the subarray is [nums[1], nums[2]] = [1, 2].
            The stable subarrays are [1], [2], and [1, 2]. The total number of stable subarrays is 3.
        For queries[2] = [0, 2], the subarray is [nums[0], nums[1], nums[2]] = [3, 1, 2].
            The stable subarrays are [3], [1], [2], and [1, 2]. The total number of stable subarrays is 4.
    Thus, ans = [2, 3, 4].

    --- Example 2 ---
    Input: nums = [2,2], queries = [[0,1],[0,0]]
    Output: [3,1]
    Explanation:
        For queries[0] = [0, 1], the subarray is [nums[0], nums[1]] = [2, 2].
            The stable subarrays are [2], [2], and [2, 2]. The total number of stable subarrays is 3.
        For queries[1] = [0, 0], the subarray is [nums[0]] = [2].
            The stable subarray is [2]. The total number of stable subarrays is 1.
    Thus, ans = [3, 1].


    *** Constraints ***
    1 <= nums.length <= 10^5
    1 <= nums[i] <= 10^5
    1 <= queries.length <= 10^5
    queries[i] = [li, ri]
    0 <= li <= ri <= nums.length - 1

*/

#include <algorithm>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 40.26% */
/* Space Beats: 98.70% */

/* Time  Complexity: O(N  +  Q * logN) */
/* Space Complexity: O(N  +  Q       ) */
class Solution {
public:
    vector<long long> countStableSubarrays(vector<int>& nums, vector<vector<int>>& queries)
    {
        const int N = nums.size();
        vector<long long> result;

        vector<int> block_starts;
        block_starts.push_back(-1);

        for (int i = 1; i < N; i++)
        {
            if (nums[i-1] > nums[i])
                block_starts.push_back(i); // Start of a new block
        }
        block_starts.push_back(N);

        const int BLOCK_STARTINGS = block_starts.size();

        // dp[i] = total number of stable subarrays before ith block
        vector<long long> prefix_sum(BLOCK_STARTINGS, 0);
        for (int i = 1; i < BLOCK_STARTINGS; i++)
        {
            // Size of previous block
            long long block_size = block_starts[i] - block_starts[i-1];

            prefix_sum[i] = prefix_sum[i-1] + (block_size * (block_size + 1)) / 2;
        }

        for (const vector<int>& query : queries)
        {
            int L = query[0];
            int R = query[1];

            // Find the first block start strictly greater than L
            auto left_block_it = upper_bound(block_starts.begin(), block_starts.end(), L);
            int left_block_idx = left_block_it - block_starts.begin();

            int next_block_start = block_starts[left_block_idx];

            if (next_block_start > R)
            {
                // L and R belong to the same non-decreasing block
                long long subarray_size = R - L + 1;
                result.push_back((subarray_size * (subarray_size + 1)) / 2);

                continue;
            }

            // Stable subarrays starting at L and ending before the next block
            long long left_block_size  = next_block_start - L;
            long long stable_subarrays = (left_block_size * (left_block_size + 1)) / 2;

            // Find the start of the block containing R
            auto right_block_it = upper_bound(block_starts.begin() + left_block_idx, block_starts.end(), R);
            int right_block_idx = right_block_it - block_starts.begin() - 1;

            int last_block_start = block_starts[right_block_idx];

            // Stable subarrays contained within the last block, ending at R
            long long right_block_size = R - last_block_start + 1;
            stable_subarrays += (right_block_size * (right_block_size + 1)) / 2;

            // Stable subarrays in complete blocks between the first and last blocks
            stable_subarrays += prefix_sum[right_block_idx] - prefix_sum[left_block_idx];

            result.push_back(stable_subarrays);
        }

        return result;
    }
};
