/*
    ============
    === EASY ===
    ============

    ===============================================
    3432) Count Partitions with Even Sum Difference
    ===============================================

    ============
    Description:
    ============

    You are given an integer array nums of length n.

    A partition is defined as an index i where 0 <= i < n - 1, splitting the
    array into two non-empty subarrays such that:

        + Left subarray contains indices [0, i].
        + Right subarray contains indices [i + 1, n - 1].

    Return the number of partitions where the difference between the sum of the
    left and right subarrays is even.

    =================================================
    FUNCTION: int countPartitions(vector<int>& nums);
    =================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [10,10,3,7,6]
    Output: 4
    Explanation:
    The 4 partitions are:
        [10], [10, 3, 7, 6] with a sum difference of 10 - 26 = -16, which is even.
        [10, 10], [3, 7, 6] with a sum difference of 20 - 16 = 4, which is even.
        [10, 10, 3], [7, 6] with a sum difference of 23 - 13 = 10, which is even.
        [10, 10, 3, 7], [6] with a sum difference of 30 - 6 = 24, which is even.

    --- Example 2 ---
    Input: nums = [1,2,2]
    Output: 0
    Explanation:
    No partition results in an even sum difference.

    --- Example 3 ---
    Input: nums = [2,4,6,8]
    Output: 3
    Explanation:
    All partitions result in an even sum difference.


    *** Constraints ***
    2 <= n == nums.length <= 100
    1 <= nums[i] <= 100

*/

#include <cstdlib>
#include <numeric>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Simple PrefixSum Solution.

*/

/* Time  Beats: 100.00% */
/* Space Beats:   0.00% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    int countPartitions(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 0;

        vector<int> prefix_sum = nums;
        partial_sum(prefix_sum.begin(), prefix_sum.end(), prefix_sum.begin());

        for (int i = 0; i < N-1; i++)
        {
            if ((prefix_sum[i] - (prefix_sum[N-1] - prefix_sum[i])) % 2 == 0)
                result++;
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This one doesn't precalculate PrefixSum, instead we calculate left_sum and
    right_sum as we go.

    This way we don't need to allocate extra O(n) Space.

*/

/* Time  Beats: 100.00% */
/* Space Beats:   0.00% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Space_Efficient {
public:
    int countPartitions(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 0;

        int left_sum = 0;
        int right_sum = accumulate(nums.begin(), nums.end(), 0);

        for (int i = 0; i+1 < N; i++)
        {
            right_sum -= nums[i];
            left_sum  += nums[i];

            if (abs(right_sum - left_sum) % 2 == 0)
                result++;
        }
        return result;
    }
};
