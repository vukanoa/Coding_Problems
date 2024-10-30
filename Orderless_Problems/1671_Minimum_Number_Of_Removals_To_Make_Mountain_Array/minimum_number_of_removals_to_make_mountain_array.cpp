#include <iostream>
#include <vector>

/*
    ============
    === HARD ===
    ============

    =======================================================
    1671) Minimum Number of Removals to Make Mountain Array
    =======================================================

    ============
    Description:
    ============

    You may recall that an array arr is a mountain array if and only if:

        arr.length >= 3
        There exists some index i (0-indexed) with 0 < i < arr.length - 1 such that:
            arr[0] < arr[1] < ... < arr[i - 1] < arr[i]
            arr[i] > arr[i + 1] > ... > arr[arr.length - 1]

    Given an integer array nums, return the minimum number of elements to
    remove to make nums a mountain array.

    =========================================================
    FUNCTION: int minimumMountainRemovals(vector<int>& nums);
    =========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,3,1]
    Output: 0
    Explanation: The array itself is a mountain array so we do not need to
                 remove any elements.

    --- Example 2 ---
    Input: nums = [2,1,1,5,6,2,3,1]
    Output: 3
    Explanation: One solution is to remove the elements at indices 0, 1, and 5,
                 making the array nums = [1,5,6,3,1].


    *** Constraints ***
    3 <= nums.length <= 1000
    1 <= nums[i] <= 10^9
    It is guaranteed that you can make a mountain array out of nums.

*/


/*
    ------------
    --- IDEA ---
    ------------

    Interesting examples:

    1.
        [2,1,1,8,9,2,3,4,3,2,7,1]

    2.
        [2,1,1,8,9,2,3,4,5,6,7,1]

    3.
        [1,2,1,1,1]         // [2, 1, 1] is IMPOSSIBLE to be a Mountain Array

*/

/* Time  Beats: 56.06% */
/* Space Beats: 67.26% */

/* Time  Complexity: O(n^2) */
/* Space Complexity: O(n)   */
class Solution {
public:
    int minimumMountainRemovals(vector<int>& nums)
    {
        const int n = nums.size();
        vector<int> LIS(n, 1); // Longest Increasing Subsequence
        vector<int> LDS(n, 1); // Longest Decreasing Subsequence

        /*
          Compute LIS up to each index

          (How many elements are strictly increasing up to an element at index
          "right", i.e. do it for every index, inclusive)
        */
        for (int right = 0; right < n; right++)
        {
            for (int left = 0; left < right; left++)
            {
                if (nums[left] < nums[right])
                    LIS[right] = max(LIS[right], LIS[left] + 1);
            }
        }

        /*
          Compute LDS from each index

          (How many elements are strictly decreasing from element at index
          "left" until the end of an array, inclusive)
        */
        for (int left = n-1; left >= 0; left--)
        {
            for (int right = n-1; right > left; right--)
            {
                if (nums[left] > nums[right])
                    LDS[left] = max(LDS[left], LDS[right] + 1);
            }
        }

        int max_mountain_length = 0;

        /*
          Find the maximum mountain length

          Since we've calculated INCLUSIVELY for both LIS and LDS, now when we
          are adding those two values together, we must subtract because we
          only want to calculate each element exactly once..
        */
        for (int i = 1; i < n-1; i++)
        {
            if (LIS[i] > 1 && LDS[i] > 1) // Valid peak
                max_mountain_length = max(max_mountain_length, LIS[i] + LDS[i] - 1);
        }

        return n - max_mountain_length;
    }
};
