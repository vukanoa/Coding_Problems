/*
    ============
    === HARD ===
    ============

    ==========================================================
    3768) Minimum Inversion Count in Subarrays of Fixed Length
    ==========================================================

    ============
    Description:
    ============

    You are given an integer array nums of length n and an integer k.

    An inversion is a pair of indices (i, j) from nums such that i < j and
    nums[i] > nums[j].

    The inversion count of a subarray is the number of inversions within it.

    Return the minimum inversion count among all subarrays of nums with length k.

    ===============================
    FUNCTION:  
    ===============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [3,1,2,5,4], k = 3
    Output: 0
    Explanation:
    We consider all subarrays of length k = 3 (indices below are relative to
    each subarray):
        [3, 1, 2] has 2 inversions: (0, 1) and (0, 2).
        [1, 2, 5] has 0 inversions.
        [2, 5, 4] has 1 inversion: (1, 2).
    The minimum inversion count among all subarrays of length 3 is 0, achieved
    by subarray [1, 2, 5].


    --- Example 2 ---
    Input: nums = [5,3,2,1], k = 4
    Output: 6
    Explanation:
    There is only one subarray of length k = 4: [5, 3, 2, 1].
    Within this subarray, the inversions are: (0, 1), (0, 2), (0, 3), (1, 2), (1, 3), and (2, 3).
    Total inversions is 6, so the minimum inversion count is 6.


    --- Example 3 ---
    Input: nums = [2,1], k = 1
    Output: 0
    Explanation:
    All subarrays of length k = 1 contain only one element, so no inversions
    are possible.
    The minimum inversion count is therefore 0.



    *** Constraints ***
    1 <= n == nums.length <= 10^5
    1 <= nums[i] <= 10^9
    1 <= k <= n

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

/* Time  Beats:  89.38% */
/* Space Beats: 100.00% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class FenwickTree {
private:
    vector<int> fenwick_sum;
    int n;

public:
    FenwickTree(int n) :
        n(n), fenwick_sum(n + 1, 0)
    {}

    int prefix_sum(int i)
    {
        int result = 0;

        while (i > 0)
        {
            result += fenwick_sum[i];

            // Clear last Set bit
            i -= i & -i;
        }

        return result;
    }

    void update(int i, int delta)
    {
        while (i <= n)
        {
            fenwick_sum[i] += delta;

            // Add Last SET bit
            i += i & -i;
        }
    }
};


class Solution {
public:
    long long minInversionCount(vector<int>& nums, int k)
    {
        if (k == 1)
            return 0LL;

        const int N = nums.size();

        /* Coordinate Compression */
        vector<int> sorted_nums = nums;
        sort(sorted_nums.begin(), sorted_nums.end());
        sorted_nums.erase(unique(sorted_nums.begin(), sorted_nums.end()), sorted_nums.end());

        const int SORTED_SIZE = sorted_nums.size();

        FenwickTree fenwick(SORTED_SIZE);

        /* Initialize Sliding Window */
        long long inversions = 0LL;

        for (int i = 0; i < k; i++)
        {
            auto it = lower_bound(sorted_nums.begin(), sorted_nums.end(), nums[i]);
            const int compressed_ifx = it - sorted_nums.begin() + 1;

            inversions += i - fenwick.prefix_sum(compressed_ifx);
            fenwick.update(compressed_ifx, 1);
        }

        long long result = inversions;

        /* Sliding Window */
        for (int i = k; i < N; i++)
        {
            /* Remove Outgoing Element */
            const int outgoing_element = nums[i - k];

            auto it = lower_bound(sorted_nums.begin(), sorted_nums.end(), outgoing_element);
            int outgoing_idx = it - sorted_nums.begin() + 1;

            inversions -= fenwick.prefix_sum(outgoing_idx - 1);
            fenwick.update(outgoing_idx, -1);

            /* Add Incoming Element */
            int incoming_element = nums[i];

            it = lower_bound(sorted_nums.begin(), sorted_nums.end(), incoming_element);
            int incoming_idx = it - sorted_nums.begin() + 1;

            inversions += (k - 1) - fenwick.prefix_sum(incoming_idx);
            fenwick.update(incoming_idx, 1);

            /* Update Result */
            result = min(result, inversions);
        }

        return result;
    }
};
