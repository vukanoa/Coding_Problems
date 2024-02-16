#include <iostream>
#include <vector>

/*
    ============
    === EASY ===
    ============

    ================================
    303) Range Sum Query - Immutable
    ================================

    ============
    Description:
    ============

    Given an integer array nums, handle multiple queries of the following type:

        Calculate the sum of the elements of nums between indices left and
        right inclusive where left <= right.

    Implement the NumArray class:

        NumArray(int[] nums) Initializes the object with the integer array
        nums.  int sumRange(int left, int right) Returns the sum of the
        elements of nums between indices left and right inclusive (i.e.
        nums[left] + nums[left + 1] + ... + nums[right]).

    ===============================
    FUNCTION:
    class NumArray {
    public:
        NumArray(vector<int>& nums)
        {
        }

        int sumRange(int left, int right)
        {
        }
    };
    ===============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input
    ["NumArray", "sumRange", "sumRange", "sumRange"]
    [[[-2, 0, 3, -5, 2, -1]], [0, 2], [2, 5], [0, 5]]
    Output
    [null, 1, -1, -3]

    Explanation
    NumArray numArray = new NumArray([-2, 0, 3, -5, 2, -1]);
    numArray.sumRange(0, 2); // return (-2) + 0 + 3 = 1
    numArray.sumRange(2, 5); // return 3 + (-5) + 2 + (-1) = -1
    numArray.sumRange(0, 5); // return (-2) + 0 + 3 + (-5) + 2 + (-1) = -3


    *** Constraints ***
    1 <= nums.length <= 10^4
    -105 <= nums[i] <= 10^5
    0 <= left <= right < nums.length
    At most 104 calls will be made to sumRange.

*/

/*
    ------------
    --- IDEA ---
    ------------

    This is a standard "trick" of how to, efficiently, calculate sum of some
    contiguous range in vector "nums".

    If we already have a prefix_sum vector, then we can retrieve the result in
    O(1).

    It's very handy if we are asked to do multiple different ranges on the same
    vector.

*/

/* Time  Beats: 94.84% */
/* Space Beats: 23.30% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class NumArray {
public:
    NumArray(vector<int>& nums)
        : helper(nums), prefix(nums.size(), 0)
    {
        for (int i = 1; i < nums.size(); i++)
            prefix[i] = prefix[i-1] + nums[i-1];
    }

    int sumRange(int left, int right)
    {
        return prefix[right] - prefix[left] + helper[right];
    }

private:
    std::vector<int> helper;
    std::vector<int> prefix;
};




/*
    ------------
    --- IDEA ---
    ------------

    Another way of implementing "sumRange" function. This is more intuitive to
    me.

    This one doesn't use any additonal "helper" vector. This one is elegant.

*/

/* Time  Beats: 84.11% */
/* Space Beats: 22.29% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class NumArray {
public:
    NumArray(vector<int>& nums)
        :prefix(nums.size(), 0)
    {
        prefix[0] = nums[0];
        for (int i = 1; i < nums.size(); i++)
            prefix[i] = prefix[i-1] + nums[i];
    }

    int sumRange(int left, int right)
    {
        if (left == 0)
            return prefix[right];

        return prefix[right] - prefix[left - 1];
    }

private:
    std::vector<int> prefix;
};
