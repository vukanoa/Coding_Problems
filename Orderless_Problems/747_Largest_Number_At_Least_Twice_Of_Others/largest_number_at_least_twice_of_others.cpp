#include <iostream>

/*
    ============
    === EASY ===
    ============

    ============================================
    747) Largest Number At Least Twice of Others
    ============================================

    ============
    Description:
    ============

    You are given an integer array nums where the largest integer is unique.

    Determine whether the largest element in the array is at least twice as
    much as every other number in the array. If it is, return the index of the
    largest element, or return -1 otherwise.

    ===============================================
    FUNCTION: int dominantIndex(vector<int>& nums); 
    ===============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [3,6,1,0]
    Output: 1
    Explanation: 6 is the largest integer.
    For every other number in the array x, 6 is at least twice as big as x.
    The index of value 6 is 1, so we return 1.

    --- Example 2 ---
    Input: nums = [1,2,3,4]
    Output: -1
    Explanation: 4 is less than twice the value of 3, so we return -1.


    *** Constraints ***
    2 <= nums.length <= 50
    0 <= nums[i] <= 100
    The largest element in nums is unique.

*/

/*
    ------------
    --- IDEA ---
    ------------

    Intuitive idea. The code is self-explanatory.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  48.46% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    int dominantIndex(vector<int>& nums)
    {
        int largest = INT_MIN;
        int second_largest = INT_MIN;

        int index = -1;
        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] > largest)
            {
                second_largest = std::max(second_largest, largest);
                largest = nums[i];
                index = i;
            }
            else
                second_largest = std::max(second_largest, nums[i]);
        }

        return 2 * second_largest <= largest ? index : -1;
    }
};
