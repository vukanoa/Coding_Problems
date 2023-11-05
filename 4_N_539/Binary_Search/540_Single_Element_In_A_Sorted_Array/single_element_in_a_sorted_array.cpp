#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    =====================================
    540) Single Element in a Sorted Array
    =====================================

    ============
    Description:
    ============

    You are given a sorted array consisting of only integers where every
    element appears exactly twice, except for one element which appears exactly
    once.

    Return the single element that appears only once.

    Your solution must run in O(log n) time and O(1) space.

    ====================================================
    FUNCTION: int singleNonDuplicate(vector<int>& nums);
    ====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,1,2,3,3,4,4,8,8]
    Output: 2

    --- Example 2 ---
    Input: nums = [3,3,7,7,10,11,11]
    Output: 10


    *** Constraints ***
    1 <= nums.length <= 10^5
    0 <= nums[i] <= 10^5

*/

/*
    ------------
    --- IDEA ---
    ------------

    [1, 1, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11]
           #

    [1, 1, 3]
           #

    [1, 3, 3]
     #

    [1]

    [1, 3, 3, 5, 5]
     #

    [1, 1, 3, 5, 5]
           #

    [1, 1, 3, 3, 5]
                 #

*/

/*
    ------------
    --- IDEA ---
    ------------

    For some reason, this implementation has better Beating times than the 2nd
    Solution down below(than the bottom one) even if this one has 3 additional
    check-ups.

    I've submitted both Solution more than 10 times, but for some reason this
    one runs faster. I have no idea why.

*/

/* Time  Beats: 90.62% */
/* Space Beats: 46.33% */

/* Time  Complexity: O(logn) */
/* Space Complexity: O(1) */
class Solution {
public:
    int singleNonDuplicate(std::vector<int>& nums)
    {
        int n = nums.size();

        int left  = 0;
        int right = n - 1;

        while (left < right)
        {
            int mid = left + (right - left) / 2;

            if (
                ((mid-1 ==-1) || (mid-1 >= 0 && nums[mid - 1] != nums[mid])) &&
                ((mid+1 == n) || (mid+1 <  n && nums[mid + 1] != nums[mid]))
               )
                return nums[mid];

            int left_one;
            if (mid-1 >= 0 && nums[mid-1] == nums[mid])
                left_one = mid-1;
            else if (mid+1 < n && nums[mid] == nums[mid+1]) // Or just else
                left_one = mid;

            /*
                Now if from the left one of two appearances, to the end of the
                vector there are EVEN number of elements, we are certain that
                the "single number" is in the left portion since we're told
                that it's guaranteed that there is only one single element in
                the entire array.
            */
            if ((n - left_one) % 2 == 0)
                right = mid;
            else
                left = mid + 1;
        }

        return nums[left];
    }
};




/* Time  Beats: 80.82% */
/* Space Beats: 46.33% */

/* Time  Complexity: O(logn) */
/* Space Complexity: O(1) */
class Solution_2 {
public:
    int singleNonDuplicate(std::vector<int>& nums)
    {
        int n = nums.size();

        int left  = 0;
        int right = n - 1;

        while (left < right)
        {
            int mid = left + (right - left) / 2;

            if (
                ((mid-1 == -1) || (nums[mid - 1] != nums[mid])) &&
                ((mid+1 ==  n) || (nums[mid + 1] != nums[mid]))
               )
                return nums[mid];

            int left_one;
            if (mid-1 >= 0 && nums[mid-1] == nums[mid])
                left_one = mid-1;
            else // if (mid+1 < n && nums[mid] == nums[mid+1])
                left_one = mid;

            /*
                Now if from the left one of two appearances, to the end of the
                vector there are EVEN number of elements, we are certain that
                the "single number" is in the left portion since we're told
                that it's guaranteed that there is only one single element in
                the entire array.
            */
            if ((n - left_one) % 2 == 0)
                right = mid;
            else
                left = mid + 1;
        }

        return nums[left];
    }
};
