/*
    ==============
    === MEDIUM ===
    ==============

    =========================================
    153) Find Minimum in Rotated Sorted Array
    =========================================

    ============
    Description:
    ============

    Suppose an array of length "n" sorted in ascending order is rotated between
    1 and n times. For ecample, the array "nums" = [0, 1, 2, 4, 5, 6, 7] might
    become:
        [4, 5, 6, 7, 0, 1, 2] if it was rotated 4 times
        [0, 1, 2, 4, 5, 6, 7] if it was rotated 7 times

    Notice that rotating an array [a[0], a[1], a[2], ..., a[n-1]] 1 time
    results in the array [a[n-1], a[0], a[1], a[2], ..., a[n-2]].

    Given the sorted rotated array "nums" of unique elements, return the
    minimum element of this array.

    You must write an algorithm that runs in O(log n) time.

    =========================================
    FUNCTION: int findMin(vector<int>& nums);
    =========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  nums = [3, 4, 5, 1, 2]
    Output: 1

    --- Example 2 ---
    Input:  nums = [4, 5, 6, 7, 0, 1, 2]
    Output: 0

    --- Example 3 ---
    Input:  [11, 13, 15, 17]
    Output: 11

    *** Constraints ***
    n = nums.length
    1 <= n <= 5000
    -5000 <= nums[i] <= 5000
    All the integers of "nums" are unique.
    "nums" is sorted and rotated between 1 and n times.

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    This is how you find the Pivot in a Rotated Sorted array.
    This is by far the simplest Solution.

*/

/* Time  Beats: 100% */
/* Space Beats: 50.98% */

/* Time  Complexity: O(logn) */
/* Space Complexity: O(1)    */
class Solution {
public:
    int findMin(vector<int>& nums)
    {
        int left  = 0;
        int right = nums.size() - 1;

        while (left < right)
        {
            int mid = left + (right - left) / 2;

            if (nums[mid] > nums[right])
                left = mid + 1;
            else
                right = mid;
        }

        return nums[right];
    }
};
