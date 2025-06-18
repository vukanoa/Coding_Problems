/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    413) Arithmetic Slices
    ===========================

    ============
    Description:
    ============

    An integer array is called arithmetic if it consists of at least three
    elements and if the difference between any two consecutive elements is the
    same.

        + For example, [1,3,5,7,9], [7,7,7,7], and [3,-1,-5,-9] are arithmetic
          sequences.

    Given an integer array nums, return the number of arithmetic subarrays of
    nums.

    A subarray is a contiguous subsequence of the array.

    ==========================================================
    FUNCTION: int numberOfArithmeticSlices(vector<int>& nums);
    ==========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,3,4]
    Output: 3
    Explanation: We have 3 arithmetic slices in nums: [1, 2, 3], [2, 3, 4] and
                 [1,2,3,4] itself.

    --- Example 2 ---
    Input: nums = [1]
    Output: 0


    *** Constraints ***
    1 <= nums.length <= 5000
    -1000 <= nums[i] <= 1000

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
/* Space Beats:  54.57% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& nums)
    {
        const int N = nums.size();

        if (N < 3)
            return 0;

        int count = 0;
        int diff  = 0;

        int idx = 0;

        int prev_diff = nums[1] - nums[0];

        for (int i = 1; i < N-1; i++)
        {
            int curr_diff = nums[i+1] - nums[i];

            // If we find same diff of consecutive elements, increase count
            if (curr_diff == prev_diff)
            {
                idx++;
            }
            else
            {
                // Update prev_diff with curr_diff as we don't find consecutive
                // elements with same diff
                prev_diff = curr_diff;
                idx = 0;
            }

            count += idx;
        }

        return count;
    }
};
