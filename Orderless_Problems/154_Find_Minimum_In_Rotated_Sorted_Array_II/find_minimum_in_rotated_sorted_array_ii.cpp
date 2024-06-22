#include <iostream>
#include <vector>

/*
    ============
    === HARD ===
    ============

    ============================================
    154) Find Minimum in Rotated Sorted Array II
    ============================================

    ============
    Description:
    ============

    Suppose an array of length n sorted in ascending order is rotated between 1
    and n times. For example, the array nums = [0,1,4,4,5,6,7] might become:

        [4,5,6,7,0,1,4] if it was rotated 4 times.  [0,1,4,4,5,6,7] if it was
        rotated 7 times.

    Notice that rotating an array [a[0], a[1], a[2], ..., a[n-1]] 1 time
    results in the array [a[n-1], a[0], a[1], a[2], ..., a[n-2]].

    Given the sorted rotated array nums that may contain duplicates, return the
    minimum element of this array.

    You must decrease the overall operation steps as much as possible.


    ---------------
    -- Follow Up --
    ---------------

       This problem is similar to "Find Minimum in Rotated Sorted Array", but
       nums may contain duplicates. Would this affect the runtime complexity?
       How and why? 

    =========================================
    FUNCTION: int findMin(vector<int>& nums); 
    =========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,3,5]
    Output: 1

    --- Example 2 ---
    Input: nums = [2,2,2,0,1]
    Output: 0


    *** Constraints ***
    n == nums.length
    1 <= n <= 5000
    -5000 <= nums[i] <= 5000
    nums is sorted and rotated between 1 and n times.

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 31.44% */
/* Space Beats: 95.24% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(1)        */
class Solution {
public:
    int findMin(vector<int>& nums)
    {
        int result = INT_MAX;

        int low  = 0;
        int high = nums.size() - 1;

        while(low <= high)
        {
            int mid = low + (high - low) / 2;

            result = std::min(result, nums[mid]);

            if (nums[low] == nums[mid] and nums[mid] == nums[high])
            {
                low++;
                high--;
                continue;
            }

            if(nums[low] < nums[mid])
            {
                // left array is sorted
                if(nums[low] >= nums[high] and nums[mid] > nums[high])
                    low = mid + 1;
                else
                    high = mid - 1;

            }
            else
            {
                // Right array is sorted
                if (nums[high] <= nums[low] and nums[mid] < nums[low])
                    high = mid - 1;
                else
                    low = mid + 1;
            }
        }

        return result;
    }
};
