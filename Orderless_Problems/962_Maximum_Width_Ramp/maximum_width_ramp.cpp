#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    962) Maximum Width Ramp
    ===========================

    ============
    Description:
    ============

    A ramp in an integer array nums is a pair (i, j) for which i < j and
    nums[i] <= nums[j]. The width of such a ramp is j - i.

    Given an integer array nums, return the maximum width of a ramp in nums. If
    there is no ramp in nums, return 0.

    ==============================================
    FUNCTION: int maxWidthRamp(vector<int>& nums);
    ==============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [6,0,8,2,1,5]
    Output: 4
    Explanation: The maximum width ramp is achieved at (i, j) = (1, 5): nums[1]
                 = 0 and nums[5] = 5.


    --- Example 2 ---
    Input: nums = [9,8,1,0,1,9,4,0,4,1]
    Output: 7
    Explanation: The maximum width ramp is achieved at (i, j) = (2, 9): nums[2]
                 = 1 and nums[9] = 1.



    *** Constraints ***
    2 <= nums.length <= 5 * 10^4
    0 <= nums[i] <= 5 * 10^4

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 45.61% */
/* Space Beats: 16.92% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    int maxWidthRamp(vector<int>& nums)
    {
        const int n = nums.size();
        vector<int> max_right(0, n);

        int prev_max = 0;
        int i = n-1;

        while (i >= 0)
        {
            max_right[i] = max(nums[i], prev_max);
            prev_max = max_right[i];

            i--;
        }

        int result = 0;

        int left  = 0;
        int right = 0;
        while (right < n)
        {
            while (nums[left] > max_right[right])
                left++;

            result = max(result, right - left);
            right++;
        }

        return result;
    }
};
