#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ============================
    2439) Minimize Maximum Array
    ============================

    ============
    Description:
    ============

    You are given a 0-indexed array nums comprising of n non-negative integers.

    In one operation, you must:

        Choose an integer i such that 1 <= i < n and nums[i] > 0.  Decrease
        nums[i] by 1.  Increase nums[i - 1] by 1.

    Return the minimum possible value of the maximum integer of nums after
    performing any number of operations.

    ====================================================
    FUNCTION: int minimizeArrayValue(vector<int>& nums);
    ====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [3,7,1,6]
    Output: 5
    Explanation:
    One set of optimal operations is as follows:
    1. Choose i = 1, and nums becomes [4,6,1,6].
    2. Choose i = 3, and nums becomes [4,6,2,5].
    3. Choose i = 1, and nums becomes [5,5,2,5].
    The maximum integer of nums is 5. It can be shown that the maximum number
    cannot be less than 5.  Therefore, we return 5.


    --- Example 2 ---
    Input: nums = [10,1]
    Output: 10
    Explanation:
    It is optimal to leave nums as is, and since 10 is the maximum value, we
    return 10.


    *** Constraints ***
    n == nums.length
    2 <= n <= 10^5
    0 <= nums[i] <= 10^9

*/

/* Time  Beats: 95.53% */
/* Space Beats: 83.76% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    int minimizeArrayValue(std::vector<int>& nums)
    {
        unsigned long long result = nums[0];
        unsigned long long total  = nums[0];

        for (int i = 1; i < nums.size(); i++)
        {
            total += nums[i];
            unsigned long long tmp = std::ceil( (1.0 * total) / (i+1) );

            result = std::max(result, tmp);
        }

        return (int)(result);
    }
};
