#include <iostream>
#include <vector>
#include <algorithm>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================================
    945) Minimum Increment To Make Array Unique
    ===========================================

    ============
    Description:
    ============

    You are given an integer array nums. In one move, you can pick an index i
    where 0 <= i < nums.length and increment nums[i] by 1.

    Return the minimum number of moves to make every value in nums unique.

    The test cases are generated so that the answer fits in a 32-bit integer.

    ===============================
    FUNCTION:
    ===============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    <++>

    --- Example 2 ---

    --- Example 3 ---

    *** Constraints ***

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 62.01% */
/* Space Beats: 79.13% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n)        */
class Solution {
public:
    int minIncrementForUnique(std::vector<int>& nums)
    {
        /* Sort */
        std::sort(nums.begin(),nums.end());

        int result = 0;
        for(int i = 1; i < nums.size(); i++)
        {
            if(nums[i] <= nums[i-1])
            {
                result  += nums[i-1] - nums[i] + 1;
                nums[i]  = nums[i-1] + 1;
            }
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    1. Sorting:
        Sort the input array to simplify sequential processing.

    2. Initialization:
        Set up variables for the target unique value and the total increments
        counter.

    3. Iteration and Adjustment:
        For each number, adjust it to at least match the last unique value,
        increasing the total increments as needed.

    4. Result:
        Return the cumulative number of increments required to ensure all
        numbers are unique.

*/

/* Time  Beats: 84.45% */
/* Space Beats: 21.06% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(1)        */
class Solution_2 {
public:
    int minIncrementForUnique(std::vector<int>& nums)
    {
        /* Sort */
        std::sort(nums.begin(), nums.end());

        int num_tracker   = 0; // Tracks next unique number that should be set.
        int min_increment = 0; // Counts the total increments required.

        for (const int& num : nums)
        {
            num_tracker    = std::max(num_tracker, num);
            min_increment += num_tracker - num;

            num_tracker   += 1; // Increment the tracker for the next number.
        }

        return min_increment;
    }
};
