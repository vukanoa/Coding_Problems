/*
    ============
    === HARD ===
    ============

    ==================================================
    2916) Subarrays Distinct Element Sum of Squares II
    ==================================================

    ============
    Description:
    ============

    You are given a 0-indexed integer array nums.

    The distinct count of a subarray of nums is defined as:

        + Let nums[i..j] be a subarray of nums consisting of all the indices
          from i to j such that 0 <= i <= j < nums.length. Then the number of
          distinct values in nums[i..j] is called the distinct count of
          nums[i..j].

    Return the sum of the squares of distinct counts of all subarrays of nums.

    Since the answer may be very large, return it modulo 109 + 7.

    A subarray is a contiguous non-empty sequence of elements within an array.

    ===========================================
    FUNCTION: int sumCounts(vector<int>& nums);
    ===========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,1]
    Output: 15
    Explanation: Six possible subarrays are:
    [1]: 1 distinct value
    [2]: 1 distinct value
    [1]: 1 distinct value
    [1,2]: 2 distinct values
    [2,1]: 2 distinct values
    [1,2,1]: 2 distinct values
    The sum of the squares of the distinct counts in all subarrays is equal to
    12 + 12 + 12 + 22 + 22 + 22 = 15.

    --- Example 2 ---
    Input: nums = [2,2]
    Output: 3
    Explanation: Three possible subarrays are:
    [2]: 1 distinct value
    [2]: 1 distinct value
    [2,2]: 1 distinct value
    The sum of the squares of the distinct counts in all subarrays is equal to
    12 + 12 + 12 = 3.


    *** Constraints ***
    1 <= nums.length <= 10^5
    1 <= nums[i] <= 10^5

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 33.77% */
/* Space Beats: 5.19% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class SegmentTree {
public:
    const int MOD = 1e9 + 7;

    void apply_lazy(int idx, int start, int end, long long delta,
                    vector<long long>& sum_tree,
                    vector<long long>& squared_sum_tree,
                    vector<long long>& lazy)
    {
        long long segment_len = end - start + 1;

        squared_sum_tree[idx] = (squared_sum_tree[idx]
                               + 2LL * delta * sum_tree[idx]
                               + delta * delta % MOD * segment_len) % MOD;

        sum_tree[idx] = (sum_tree[idx] + delta * segment_len) % MOD;
    }

    void propagate_lazy(int idx, int start, int end,
                        vector<long long>& sum_tree,
                        vector<long long>& squared_sum_tree,
                        vector<long long>& lazy)
    {
        if (lazy[idx] == 0 || start == end)
            return;

        int mid = start + (end - start) / 2;
        long long delta = lazy[idx];

        apply_lazy(2 * idx + 1, start, mid, delta,
                   sum_tree, squared_sum_tree, lazy);

        apply_lazy(2 * idx + 2, mid + 1, end, delta,
                   sum_tree, squared_sum_tree, lazy);

        lazy[2 * idx + 1] = (lazy[2 * idx + 1] + delta) % MOD;
        lazy[2 * idx + 2] = (lazy[2 * idx + 2] + delta) % MOD;

        lazy[idx] = 0;
    }

    void lazy_range_add(int idx, int start, int end,
                        int q_left, int q_right, int delta,
                        vector<long long>& sum_tree,
                        vector<long long>& squared_sum_tree,
                        vector<long long>& lazy)
    {
        if (start > end || q_right < start || end < q_left)
            return;

        if (q_left <= start && end <= q_right)
        {
            apply_lazy(idx, start, end, delta,
                       sum_tree, squared_sum_tree, lazy);

            lazy[idx] = (lazy[idx] + delta) % MOD;
            return;
        }

        propagate_lazy(idx, start, end,
                       sum_tree, squared_sum_tree, lazy);

        int mid = start + (end - start) / 2;

        lazy_range_add(2 * idx + 1, start, mid, q_left, q_right, delta,
                       sum_tree, squared_sum_tree, lazy);

        lazy_range_add(2 * idx + 2, mid + 1, end, q_left, q_right, delta,
                       sum_tree, squared_sum_tree, lazy);

        sum_tree[idx] = (sum_tree[2 * idx + 1]
                       + sum_tree[2 * idx + 2]) % MOD;

        squared_sum_tree[idx] = (squared_sum_tree[2 * idx + 1]
                               + squared_sum_tree[2 * idx + 2]) % MOD;
    }
};

class Solution {
public:
    int sumCounts(vector<int>& nums)
    {
        const int N = nums.size();
        const long long MOD = 1e9 + 7;

        vector<int> last_occurrence(1e5 + 1, -1);

        vector<long long> sum_tree(4 * N, 0);
        vector<long long> squared_sum_tree(4 * N, 0);
        vector<long long> lazy(4 * N, 0);

        SegmentTree segment_tree;

        long long result = 0;

        for (int right = 0; right < N; right++)
        {
            int left = last_occurrence[nums[right]] + 1;
            last_occurrence[nums[right]] = right;

            segment_tree.lazy_range_add(
                0, 0, N - 1, left, right, 1,
                sum_tree, squared_sum_tree, lazy
            );

            result = (result + squared_sum_tree[0]) % MOD;
        }

        return result;
    }
};
