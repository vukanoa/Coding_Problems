#include <iostream>

/*
    ==============
    === MEDIUM ===
    ==============

    ============================
    523) Continuous Subarray Sum
    ============================

    ============
    Description:
    ============

    Given an integer array nums and an integer k, return true if nums has a
    good subarray or false otherwise.

    A good subarray is a subarray where:

        its length is at least two, and the sum of the elements of the subarray
        is a multiple of k.

    Note that:

        A subarray is a contiguous part of the array.  An integer x is a
        multiple of k if there exists an integer n such that x = n * k. 0 is
        always a multiple of k.

    ==========================================================
    FUNCTION: bool checkSubarraySum(vector<int>& nums, int k);
    ==========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [23,2,4,6,7], k = 6
    Output: true
    Explanation: [2, 4] is a continuous subarray of size 2 whose elements sum
                 up to 6.


    --- Example 2 ---
    Input: nums = [23,2,6,4,7], k = 6
    Output: true
    Explanation: [23, 2, 6, 4, 7] is an continuous subarray of size 5 whose
                 elements sum up to 42.  42 is a multiple of 6 because 42 = 7 *
                 6 and 7 is an integer.


    --- Example 3 ---
    Input: nums = [23,2,6,4,7], k = 13
    Output: false


    *** Constraints ***
    1 <= nums.length <= 10^5
    0 <= nums[i] <= 10^9
    0 <= sum(nums[i]) <= 2^31 - 1
    1 <= k <= 2^31 - 1

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO
    
*/

/* Time  Beats: 94.51% */
/* Space Beats: 77.30% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k)
    {
        std::unordered_map<int, int> remainder;
        remainder.insert({0, -1});

        int prefix = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            prefix += nums[i];

            if (remainder.find(prefix % k) != remainder.end())
            {
                if (i - remainder[prefix % k] > 1)
                    return true;
            }
            else
                remainder.insert({prefix % k, i});
        }

        return false;
    }
};
