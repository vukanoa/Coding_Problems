/*
    ============
    === EASY ===
    ============

    =================================================
    2913) Subarrays Distinct Element Sum of Squares I
    =================================================

    ============
    Description:
    ============

    You are given a 0-indexed integer array nums.

    The distinct count of a subarray of nums is defined as:

        Let nums[i..j] be a subarray of nums consisting of all the indices from
        i to j such that 0 <= i <= j < nums.length. Then the number of distinct
        values in nums[i..j] is called the distinct count of nums[i..j].

    Return the sum of the squares of distinct counts of all subarrays of nums.

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
    The sum of the squares of the distinct counts in all subarrays is equal to 12 + 12 + 12 + 22 + 22 + 22 = 15.

    --- Example 2 ---
    Input: nums = [1,1]
    Output: 3
    Explanation: Three possible subarrays are:
    [1]: 1 distinct value
    [1]: 1 distinct value
    [1,1]: 1 distinct value
    The sum of the squares of the distinct counts in all subarrays is equal to 12 + 12 + 12 = 3.


    *** Constraints ***
    1 <= nums.length <= 100
    1 <= nums[i] <= 100

*/

#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 92.87% */
/* Space Beats: 92.68% */

/* Time  Complexity: O(N log N) */
/* Space Complexity: O(N)       */
class SegmentTree {
private:
    vector<long long> sum1;
    vector<long long> sum2;
    vector<long long> lazy;

public:
    SegmentTree(int n)
    {
        sum1.assign(4 * n, 0);
        sum2.assign(4 * n, 0);
        lazy.assign(4 * n, 0);
    }

    void apply(int idx, int start, int end, long long delta)
    {
        long long len = end - start + 1;

        sum2[idx] += 2LL * delta * sum1[idx] +
                     len * delta * delta;

        sum1[idx] += len * delta;

        lazy[idx] += delta;
    }

    void push(int idx, int start, int end)
    {
        if (lazy[idx] == 0 || start == end)
            return;

        int mid = start + (end - start) / 2;

        apply(2 * idx + 1, start, mid, lazy[idx]);
        apply(2 * idx + 2, mid+1, end, lazy[idx]);

        lazy[idx] = 0;
    }

    void pull(int idx)
    {
        sum1[idx] = sum1[2 * idx + 1] + sum1[2 * idx + 2];
        sum2[idx] = sum2[2 * idx + 1] + sum2[2 * idx + 2];
    }

    void range_add(int idx, int start, int end, int q_left, int q_right, long long delta)
    {
        if (q_left <= start && end <= q_right) // Total Overlap
        {
            apply(idx, start, end, delta);
            return;
        }

        if (q_right < start || end < q_left) // No Overlap
            return;


        push(idx, start, end);

        int mid = start + (end - start) / 2;

        range_add(2*idx + 1, start, mid, q_left, q_right, delta);
        range_add(2*idx + 2, mid+1, end, q_left, q_right, delta);

        pull(idx);
    }

    long long query_sum2()
    {
        return sum2[0];
    }
};

class Solution {
public:
    int sumCounts(vector<int>& nums)
    {
        int N = nums.size();
        long long result = 0;

        SegmentTree seg_tree(N);

        unordered_map<int, int> last_pos;
        for (int right = 0; right < N; right++)
        {
            int prev = -1;

            if (last_pos.count(nums[right]))
                prev = last_pos[nums[right]];

            seg_tree.range_add(0, 0, N-1, prev+1, right, 1);
            result += seg_tree.query_sum2();

            last_pos[nums[right]] = right;
        }

        return result;
    }
};
