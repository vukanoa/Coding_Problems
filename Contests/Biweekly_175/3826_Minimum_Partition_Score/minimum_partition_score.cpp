/*
    ============
    === HARD ===
    ============

    =============================
    3826) Minimum Partition Score
    =============================

    ============
    Description:
    ============

    You are given an integer array nums and an integer k.

    Your task is to partition nums into exactly k subarrays and return an
    integer denoting the minimum possible score among all valid partitions.

    The score of a partition is the sum of the values of all its subarrays.

    The value of a subarray is defined as sumArr * (sumArr + 1) / 2, where
    sumArr is the sum of its elements.

    ================================================================
    FUNCTION: long long minPartitionScore(vector<int>& nums, int k);
    ================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [5,1,2,1], k = 2
    Output: 25
    Explanation:
        We must partition the array into k = 2 subarrays. One optimal partition is [5] and [1, 2, 1].
        The first subarray has sumArr = 5 and value = 5 × 6 / 2 = 15.
        The second subarray has sumArr = 1 + 2 + 1 = 4 and value = 4 × 5 / 2 = 10.
        The score of this partition is 15 + 10 = 25, which is the minimum possible score.

    --- Example 2 ---
    Input: nums = [1,2,3,4], k = 1
    Output: 55
    Explanation:
        Since we must partition the array into k = 1 subarray, all elements belong to the same subarray: [1, 2, 3, 4].
        This subarray has sumArr = 1 + 2 + 3 + 4 = 10 and value = 10 × 11 / 2 = 55.​​​​​​​
        The score of this partition is 55, which is the minimum possible score.

    --- Example 3 ---
    Input: nums = [1,1,1], k = 3
    Output: 3
    Explanation:
        We must partition the array into k = 3 subarrays. The only valid partition is [1], [1], [1].
        Each subarray has sumArr = 1 and value = 1 × 2 / 2 = 1.
        The score of this partition is 1 + 1 + 1 = 3, which is the minimum possible score.


    *** Constraints ***
    1 <= nums.length <= 1000
    1 <= nums[i] <= 10^4
    1 <= k <= nums.length 

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 36.45% */
/* Space Beats: 26.17% */

/* Time  Complexity: O(N^2 * k) */
/* Space Complexity: O(N   * k) */
class Solution {
public:
    long long INF = 1e18;

    int n;
    vector<vector<long long>> dp;
    vector<long long> prefix_sum;

    long long minPartitionScore(vector<int>& nums, int k)
    {
        n = nums.size();

        prefix_sum.assign(n, 0);
        prefix_sum[0] = nums[0];
        for (int i = 1; i < n; i++)
            prefix_sum[i] = prefix_sum[i - 1] + nums[i];

        dp.assign(n, vector<long long>(k + 1, -1));

        return solve(0, k);
    }

private:
    long long solve(int idx, int k)
    {
        if (idx == n && k == 0)
            return 0;

        if (idx == n || k == 0)
            return INF;

        if (dp[idx][k] != -1)
            return dp[idx][k];

        long long result = INF;

        for (int i = idx; i <= n - k; i++)
        {
            // sum of nums[idx..i] = pref[i] - pref[idx - 1]
            long long curr = (idx == 0) ? prefix_sum[i] : prefix_sum[i] - prefix_sum[idx - 1];
            long long cost = curr * (curr + 1) / 2;

            if (cost >= result)
                break;

            result = min(result, cost + solve(i + 1, k - 1));
        }

        return dp[idx][k] = result;
    }
};
