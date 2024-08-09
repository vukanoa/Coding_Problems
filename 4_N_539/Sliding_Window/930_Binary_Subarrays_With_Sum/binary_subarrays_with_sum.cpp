#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ==============================
    930) Binary Subarrays with Sum
    ==============================

    ============
    Description:
    ============

    Given a binary array nums and an integer goal, return the number of
    non-empty subarrays with a sum goal.

    A subarray is a contiguous part of the array.

    ===============================================================
    FUNCTION: int numSubarraysWithSum(vector<int>& nums, int goal);
    ===============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,0,1,0,1], goal = 2
    Output: 4
    Explanation: The 4 subarrays are bolded and underlined below:
    [1,0,1,0,1]
    [1,0,1,0,1]
    [1,0,1,0,1]
    [1,0,1,0,1]


    --- Example 2 ---
    Input: nums = [0,0,0,0,0], goal = 0
    Output: 15


    *** Constraints ***
    1 <= nums.length <= 3 * 10^4
    nums[i] is either 0 or 1.
    0 <= goal <= nums.length

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 82.17% */
/* Space Beats: 59.55% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    int numSubarraysWithSum(vector<int>& nums, int goal)
    {
        return helper(nums, goal) - helper(nums, goal - 1);
    }

private:
    int helper(vector<int>& nums, int x)
    {
        if (x < 0)
            return 0;

        int L = 0;
        int R = 0;

        int sum = 0;
        int result = 0;

        while (R < nums.size())
        {
            sum += nums[R];

            while (sum > x)
            {
                sum -= nums[L];
                L++;
            }

            result += R - L + 1;
            R++;
        }

        return result;
    }
};
