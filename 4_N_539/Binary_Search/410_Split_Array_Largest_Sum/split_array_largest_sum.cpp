#include <iostream>
#include <vector>

/*
    ============
    === HARD ===
    ============

    ============================
    410) Split Array Largest Sum
    ============================

    ============
    Description:
    ============

    Given an integer array nums and an integer k, split nums into k non-empty
    subarrays such that the largest sum of any subarray is minimized.

    Return the minimized largest sum of the split.

    A subarray is a contiguous part of the array.

    ===================================================
    FUNCTION: int splitArray(vector<int>& nums, int k);
    ===================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [7,2,5,10,8], k = 2
    Output: 18
    Explanation: There are four ways to split nums into two subarrays.
    The best way is to split it into [7,2,5] and [10,8], where the largest sum
    among the two subarrays is only 18.


    --- Example 2 ---
    Input: nums = [1,2,3,4,5], k = 2
    Output: 9
    Explanation: There are four ways to split nums into two subarrays.
    The best way is to split it into [1,2,3] and [4,5], where the largest sum
    among the two subarrays is only 9.


    *** Constraints ***
    1 <= nums.length <= 1000
    0 <= nums[i] <= 10^6
    1 <= k <= min(50, nums.length)

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats: 59.36%  */

/* Time  Complexity: O(n * log( sum(nums) )) */
/* Space Complexity: O(1)                    */
class Solution {
public:
    int splitArray(std::vector<int>& nums, int m)
    {
        int n = nums.size();

        int left  = 0;
        int right = 0;
        for(int i = 0; i < n; i++)
            left = std::max(left, nums[i]), right += nums[i];

        int mid = 0;
        int result = 0;

        while(left <= right)
        {
            int mid = left + (right - left) / 2; // Left plus half of the range

            int count = 0;
            int sum_tmp = 0;
            for(int i = 0; i < n;++i)
            {
                if(sum_tmp + nums[i] <= mid)
                    sum_tmp += nums[i];
                else
                {
                    count++;
                    sum_tmp = nums[i];
                }
            }
            count++;

            if(count <= m)
            {
                right = mid - 1;
                result = mid;
            }
            else
                left = mid + 1;
        }

        return result;
    }
};
