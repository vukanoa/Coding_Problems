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

#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  89.61% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Sum_Fenwick {
private:
    vector<long long> sum_fenwick;
    int n;

public:
    Sum_Fenwick(int n)
        : n(n), sum_fenwick(n + 1, 0)
    {}

    long long sum(int i)
    {
        long long result = 0;

        while (i > 0)
        {
            result += sum_fenwick[i];
            i -= i & -i;
        }

        return result;
    }

    void increase(int idx, long long delta)
    {
        int i = idx;

        while (i <= n)
        {
            sum_fenwick[i] += delta;
            i += i & -i;
        }
    }
};

class Solution {
public:
    int sumCounts(vector<int>& nums)
    {
        const int N = nums.size();
        const long long MOD = 1e9 + 7;

        Sum_Fenwick count(N);
        Sum_Fenwick total(N);
        unordered_map<int, int> last_occurrence_idx;

        long long result = 0;

        for (int right = 0; right < N; right++)
        {
            int prev_ocurrence_idx = last_occurrence_idx.count(nums[right]) ? last_occurrence_idx[nums[right]] : -1;

            long long count_of_positions = count.sum(N - prev_ocurrence_idx - 1);
            long long sum_of_positions   = total.sum(N - prev_ocurrence_idx - 1);

            long long gain = 1LL * (right - prev_ocurrence_idx) * (right - prev_ocurrence_idx)
                           - 2LL * (sum_of_positions - 1LL * prev_ocurrence_idx * count_of_positions);

            result = (result + 1LL * (N - right) * gain) % MOD;

            if (prev_ocurrence_idx >= 0)
            {
                count.increase(N - prev_ocurrence_idx, 1);
                total.increase(N - prev_ocurrence_idx, prev_ocurrence_idx);
            }

            last_occurrence_idx[nums[right]] = right;
        }

        return result;
    }
};
