#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ============================================
    1658) Minimum Operations to Reduce X to Zero
    ============================================

    ============
    Description:
    ============

    You are given an integer array nums and an integer x. In one operation, you
    can either remove the leftmost or the rightmost element from the array nums
    and subtract its value from x. Note that this modifies the array for future
    operations.

    Return the minimum number of operations to reduce x to exactly 0 if it is
    possible, otherwise, return -1.

    ======================================================
    FUNCTION: int minOperations(vector<int>& nums, int x);
    ======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,1,4,2,3], x = 5
    Output: 2
    Explanation: The optimal solution is to remove the last two elements to
                 reduce x to zero.


    --- Example 2 ---
    Input: nums = [5,6,7,8,9], x = 4
    Output: -1


    --- Example 3 ---
    Input: nums = [3,2,20,1,1,3], x = 10
    Output: 5
    Explanation: The optimal solution is to remove the last three elements and
                 the first two elements (5 operations in total) to reduce x to
                 zero.


    *** Constraints ***
    1 <= nums.length <= 10^5
    1 <= nums[i] <= 10^4
    1 <= x <= 10^9

*/

/*
    ------------
    --- IDEA ---
    ------------

    Think of it in a reverse sense.

    This is a good example to show how difficult it would be if we were to do
    it in a way they're describing.

    nums = [3, 2, 2, 9, 6, 1, 1, 2, 3],  x = 7

    TODO

*/

/* Time  Beats: 66.58% */
/* Space Beats: 84.75% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    int minOperations(std::vector<int>& nums, int x)
    {
        int sum = 0;
        for (int& num : nums)
            sum += num;

        int target   = sum - x;
        int curr_sum = 0;

        int left  = 0;
        int right = 0;

        int max_window = -1; // Middle window, that's why it's "maximum"
        while (right < nums.size())
        {
            curr_sum += nums[right];

            while (left <= right && curr_sum > target)
                curr_sum -= nums[left++];

            if (curr_sum == target)
                max_window = std::max(max_window, right - left + 1);

            right++;
        }

        return max_window == -1 ? -1 : nums.size() - max_window;
    }
};
