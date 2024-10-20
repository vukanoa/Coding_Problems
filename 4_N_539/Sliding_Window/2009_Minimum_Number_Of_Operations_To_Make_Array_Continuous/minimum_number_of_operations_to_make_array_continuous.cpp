#include <iostream>
#include <vector>

/*
    ============
    === HARD ===
    ============

    ===========================================================
    2009) Minimum Number of Operations to Make Array Continuous
    ===========================================================

    ============
    Description:
    ============

    You are given an integer array nums. In one operation, you can replace any
    element in nums with any integer.

    nums is considered continuous if both of the following conditions are
    fulfilled:

        + All elements in nums are unique.
        + The difference between the maximum element and the minimum element in
          nums equals nums.length - 1.

    For example, nums = [4, 2, 5, 3] is continuous, but nums = [1, 2, 3, 5, 6]
    is not continuous.

    Return the minimum number of operations to make nums continuous.

    ===============================================
    FUNCTION: int minOperations(vector<int>& nums);
    ===============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [4,2,5,3]
    Output: 0
    Explanation: nums is already continuous.

    --- Example 2 ---
    Input: nums = [1,2,3,5,6]
    Output: 1
    Explanation: One possible solution is to change the last element to 4.
    The resulting array is [1,2,3,5,4], which is continuous.

    --- Example 3 ---
    Input: nums = [1,10,100,1000]
    Output: 3
    Explanation: One possible solution is to:
    - Change the second element to 2.
    - Change the third element to 3.
    - Change the fourth element to 4.
    The resulting array is [1,2,3,4], which is continuous.


    *** Constraints ***
    1 <= nums.length <= 10^5
    1 <= nums[i] <= 10^9

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  91.99% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n)        */
class Solution {
public:
    int minOperations(vector<int>& nums)
    {
        // Get the sorted and unique integers
        int n = nums.size();

        sort(nums.begin(), nums.end());

        int k = unique(nums.begin(), nums.end()) - nums.begin();

        // Slide the window within a valid range
        int result = INT_MAX;

        int left  = 0;
        int right = 0;
        while (right < k)
        {
            while ((left < right) && ((nums[left] + n - 1) < nums[right]))
                left++;

            result = min(result, n - (right - left + 1));

            right++;
        }

        return result;
    }
};
