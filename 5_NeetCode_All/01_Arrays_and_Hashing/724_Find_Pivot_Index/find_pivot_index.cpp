#include <iostream>
#include <vector>

/*
    ============
    === EASY ===
    ============

    ===========================
    724) Find Pivot Index
    ===========================

    ============
    Description:
    ============

    Given an array of integers nums, calculate the pivot index of this array.

    The pivot index is the index where the sum of all the numbers strictly to
    the left of the index is equal to the sum of all the numbers strictly to
    the index's right.

    If the index is on the left edge of the array, then the left sum is 0
    because there are no elements to the left. This also applies to the right
    edge of the array.

    Return the leftmost pivot index. If no such index exists, return -1.

    ==========
    == NOTE == This question is same as 1991.
    ==========

    ============================================
    FUNCTION: int pivotIndex(vector<int>& nums);
    ============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,7,3,6,5,6]
    Output: 3
    Explanation:
    The pivot index is 3.
    Left sum = nums[0] + nums[1] + nums[2] = 1 + 7 + 3 = 11
    Right sum = nums[4] + nums[5] = 5 + 6 = 11


    --- Example 2 ---
    Input: nums = [1,2,3]
    Output: -1
    Explanation:
    There is no index that satisfies the conditions in the problem statement.


    --- Example 3 ---
    Input: nums = [2,1,-1]
    Output: 0
    Explanation:
    The pivot index is 0.
    Left sum = 0 (no elements to the left of index 0)
    Right sum = nums[1] + nums[2] = 1 + -1 = 0

    *** Constraints ***
    1 <= nums.length <= 104
    -1000 <= nums[i] <= 1000

*/

/* Time  Beats: 72.16% */
/* Space Beats:  6.04% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Naive {
public:
    int pivotIndex(std::vector<int>& nums)
    {
        int n = nums.size();
        std::vector<int> dp_left (n, 0);
        std::vector<int> dp_right(n, 0);

        for (int i = 1; i < n; i++)
            dp_left[i] = nums[i-1] + dp_left[i-1];

        for (int i = n-2; i >= 0; i--)
            dp_right[i] = nums[i+1] + dp_right[i+1];

        for (int i = 0; i < n; i++)
        {
            if (dp_left[i] == dp_right[i])
                return i;
        }

        return -1;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Almost equivalent idea, but written in a way that uses O(1) Space and has
    one less for loop.

*/

/* Time  Beats: 90.30% */
/* Space Beats: 81.17% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Optimized {
public:
    int pivotIndex(std::vector<int>& nums)
    {
        int right_sum = std::accumulate(nums.begin(), nums.end(), 0);

        int left_sum = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            if (left_sum == (right_sum - nums[i]))
                return i;

            left_sum  += nums[i];
            right_sum -= nums[i];
        }

        return -1;
    }
};
