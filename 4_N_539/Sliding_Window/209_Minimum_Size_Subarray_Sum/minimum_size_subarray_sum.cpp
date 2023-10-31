#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ==============================
    209) Minimum Size Subarray Sum
    ==============================

    ============
    Description:
    ============

    Given an array of positive integers nums and a positive integer target,
    return the minimal length of a subarray whose sum is greater than or equal
    to target. If there is no such subarray, return 0 instead.

    ============================================================
    FUNCTION: int minSubarrayLen(int target, vector<int>& nums);
    ============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: target = 7, nums = [2,3,1,2,4,3]
    Output: 2
    Explanation: The subarray [4,3] has the minimal length under the problem
                 constraint.

    --- Example 2 ---
    Input: target = 4, nums = [1,4,4]
    Output: 1

    --- Example 3 ---
    Input: target = 11, nums = [1,1,1,1,1,1,1,1]
    Output: 0

    *** Constraints ***
    1 <= target <= 10^9
    1 <= nums.length <= 10^5
    1 <= nums[i] <= 10^4

*/

/*
    ------------
    --- IDEA ---
    ------------

    Classic Sliding Window technique.

*/

/* Time  Beats: 77.55% */
/* Space Beats: 41.75% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums)
    {
        int min_length = INT_MAX;

        int sum   = 0;
        int left  = 0;
        while (right < nums.size())
        {
            sum += nums[right];

            while (sum >= target)
            {
                min_length = std::min(min_length, right - left + 1);
                sum -= nums[left++];
            }

            right++;
        }

        return min_length == INT_MAX ? 0 : min_length;
    }
};
