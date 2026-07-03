/*
    ============
    === HARD ===
    ============

    ==================================================
    3956) Maximum Sum of M Non-Overlapping Subarrays I
    ==================================================

    ============
    Description:
    ============

    You are given an integer array nums of length n, and three integers m, l,
    and r.

    Your task is to select at least one and at most m non-overlapping from nums
    such that:

        + Each selected subarray has a length between [l, r] (inclusive).
        + The total sum of all selected subarrays is maximized.

    Return the maximum total sum you can achieve.

    =======================================================================
    FUNCTION: long long maximumSum(vector<int>& nums, int m, int l, int r);
    =======================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [4,1,-5,2], m = 2, l = 1, r = 3
    Output: 7
    Explanation:
    One optimal strategy is to:
        Select the subarray [4, 1] with sum 4 + 1 = 5 and the subarray [2] with
        sum 2. Both subarrays have length between [l, r]. The total sum of
        these subarrays is 5 + 2 = 7, which is the maximum achievable sum with
        at most m = 2 subarrays.

    --- Example 2 ---
    Input: nums = [1,0,3,4], m = 2, l = 1, r = 2
    Output: 8
    Explanation:
    One optimal strategy is to:
        Select the subarray [1] with sum 1 and the subarray [3, 4] with sum 3 +
        4 = 7. Both subarrays have length between [l, r]. The total sum of
        these subarrays is 1 + 7 = 8, which is the maximum achievable sum with
        at most m = 2 subarrays.

    --- Example 3 ---
    Input: nums = [-1,7,-4], m = 1, l = 2, r = 3
    Output: 6
    Explanation:
        Select the subarray [-1, 7] from nums which has length between [l, r].
        The total sum of this subarray is -1 + 7 = 6, which is the maximum
        achievable sum with at most m = 1 subarray.

    --- Example 4 ---
    Input: nums = [-3,-4,-1], m = 2, l = 1, r = 2
    Output: -1
    Explanation:
        All subarrays of nums have negative sums. The optimal strategy is to
        select the subarray [-1], which has length between [l, r]. The total
        sum of this subarray is -1, which is the maximum achievable sum with at
        most m = 2 subarrays.


    *** Constraints ***
    1 <= n == nums.length <= 1000
    -109 <= nums[i] <= 10^9
    1 <= m <= n
    1 <= l <= r <= n

*/

#include <climits>
#include <deque>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    THis one is WAAAAAAAAAAAAAAAAAY too difficult. My brain huts.

    I really advise you NOT to even try this one. Just skip it and move on with
    your life.

*/

/* Time  Beats: 19.95% */
/* Space Beats: 27.34% */

/* Time  Complexity: O(m * N  +  (r - l + 1)) */
/* Space Complexity: O(m * N)                 */
class Solution {
private:
    vector<vector<long long>> dp;
    vector<long long> prefix_sum;

public:
    long long maximumSum(vector<int>& nums, int m, int l, int r)
    {
        const int N = nums.size();

        dp.assign(m + 1, vector<long long>(N + 1, LLONG_MIN));

        prefix_sum.assign(N + 1, 0);
        for (int i = 0; i < N; i++)
            prefix_sum[i + 1] = prefix_sum[i] + nums[i];

        for (int i = 0; i <= N; i++)
            dp[0][i] = 0;

        long long maximum_sum = LLONG_MIN;

        for (int used_subarrays = 1; used_subarrays <= m; used_subarrays++)
        {
            dp[used_subarrays][N] = 0;

            deque<int> candidate_end_indices; // Monotonically decreasing

            for (int start_idx = N-1; start_idx >= 0; start_idx--)
            {
                if (start_idx + l <= N)
                {
                    long long current_value = prefix_sum[start_idx + l] +
                                              dp[used_subarrays - 1][start_idx + l];

                    while ( ! candidate_end_indices.empty())
                    {
                        int back_index = candidate_end_indices.back();

                        long long back_value = prefix_sum[back_index] +
                                               dp[used_subarrays - 1][back_index];

                        if (back_value >= current_value)
                            break;

                        candidate_end_indices.pop_back();
                    }

                    candidate_end_indices.push_back(start_idx + l);
                }

                while ( ! candidate_end_indices.empty() &&
                          candidate_end_indices.front() > start_idx + r)
                {
                    candidate_end_indices.pop_front();
                }

                dp[used_subarrays][start_idx] = dp[used_subarrays][start_idx + 1];

                if ( ! candidate_end_indices.empty())
                {
                    int end_idx = candidate_end_indices.front();

                    dp[used_subarrays][start_idx] = max(dp[used_subarrays][start_idx], dp[used_subarrays - 1][end_idx] +
                                                                                           prefix_sum[end_idx] -
                                                                                           prefix_sum[start_idx]);
                }
            }

            maximum_sum = max(maximum_sum, dp[used_subarrays][0]);
        }

        if (maximum_sum == 0)
        {
            long long best_single_subarray_sum = LLONG_MIN;

            for (int start_idx = 0; start_idx < N; start_idx++)
            {
                for (int subarray_len = l; subarray_len <= r && start_idx + subarray_len <= N; subarray_len++)
                {
                    best_single_subarray_sum = max(best_single_subarray_sum, prefix_sum[start_idx + subarray_len] -
                                                                             prefix_sum[start_idx]);
                }
            }

            return best_single_subarray_sum;
        }

        return maximum_sum;
    }
};
