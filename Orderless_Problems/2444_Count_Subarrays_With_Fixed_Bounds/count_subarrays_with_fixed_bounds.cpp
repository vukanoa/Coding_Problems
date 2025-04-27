/*
    ============
    === HARD ===
    ============

    =======================================
    2444) Count Subarrays with Fixed Bounds
    =======================================

    ============
    Description:
    ============

    You are given an integer array nums and two integers minK and maxK.

    A fixed-bound subarray of nums is a subarray that satisfies the following
    conditions:

        + The minimum value in the subarray is equal to minK.
        + The maximum value in the subarray is equal to maxK.

    Return the number of fixed-bound subarrays.

    A subarray is a contiguous part of an array.

    ==========================================================================
    FUNCTION: long long countSubarrays(vector<int>& nums, int minK, int maxK);
    ==========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,3,5,2,7,5], minK = 1, maxK = 5
    Output: 2
    Explanation: The fixed-bound subarrays are [1,3,5] and [1,3,5,2].

    --- Example 2 ---
    Input: nums = [1,1,1,1], minK = 1, maxK = 1
    Output: 10
    Explanation: Every subarray of nums is a fixed-bound subarray. There are 10
                 possible subarrays.


    *** Constraints ***
    2 <= nums.length <= 10^5
    1 <= nums[i], minK, maxK <= 10^6

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  62.77% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    long long countSubarrays(vector<int>& nums, int minK, int maxK)
    {
        const int N = nums.size();
        long long result = 0;

        int latest_minK_idx = -1;
        int latest_maxK_idx = -1;
        int latest_bad_idx  = -1; // Points to elem that is < minK and > maxK

        for (int i = 0; i < N; i++)
        {
            if (nums[i] == minK)
                latest_minK_idx = i;

            if (nums[i] == maxK)
                latest_maxK_idx = i;

            if (nums[i] < minK || nums[i] > maxK)
                latest_bad_idx = i;

            int valid_start = min(latest_minK_idx, latest_maxK_idx);
            if (valid_start > latest_bad_idx)
                result += valid_start - latest_bad_idx;
        }

        return result;
    }
};
