#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    =====================================
    81) Search in Rotated Sorted Array II
    =====================================

    ============
    Description:
    ============

    There is an integer array nums sorted in non-decreasing order (not
    necessarily with distinct values).

    Before being passed to your function, nums is rotated at an unknown pivot
    index k (0 <= k < nums.length) such that the resulting array is [nums[k],
    nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]] (0-indexed).
    For example, [0,1,2,4,4,4,5,6,6,7] might be rotated at pivot index 5 and
    become [4,5,6,6,7,0,1,2,4,4].

    Given the array nums after the rotation and an integer target, return true
    if target is in nums, or false if it is not in nums.

    You must decrease the overall operation steps as much as possible.

    Follow up: This problem is similar to Search in Rotated Sorted Array, but
               nums may contain duplicates. Would this affect the runtime
               complexity? How and why?

    =====================================================
    FUNCTION: bool search(vector<int>& nums, int target);
    =====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [2,5,6,0,0,1,2], target = 0
    Output: true

    --- Example 2 ---
    Input: nums = [2,5,6,0,0,1,2], target = 3
    Output: false


    *** Constraints ***
    1 <= nums.length <= 5000
    -10^4 <= nums[i] <= 10^4
    nums is guaranteed to be rotated at some pivot.
    -10^4 <= target <= 10^4

*/


/*
    ------------
    --- IDEA ---
    ------------

    TODO

    Examples that show why this problem isn't possible to do in the same way
    as the first version of this problem.

    [0, 5, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]

    [2, 2, 2, 1, 2, 2]

    [2, 1, 2, 2, 2, 2]

*/

/* Time  Beats: 100.00% */
/* Space Beats:  72.82% */

/* Time  Complexity: O(n) */ // O(logn) sometimes so it's faster than just O(n)
/* Space Complexity: O(1) */
class Solution {
public:
    bool search(vector<int>& nums, int target)
    {
        int left  = 0;
        int right = nums.size() - 1;

        while (left <= right)
        {
            int mid = left + (right - left) / 2;

            if (target == nums[mid])
                return true;

            if (nums[left] < nums[mid])
            {
                if (nums[left] <= target && target < nums[mid])
                    right = mid - 1;
                else
                    left  = mid + 1;
            }
            else if (nums[left] > nums[mid])
            {
                if (nums[mid] < target && target <= nums[right])
                    left  = mid + 1;
                else
                    right = mid - 1;
            }
            else
                left++;
        }

        return false;
    }
};
