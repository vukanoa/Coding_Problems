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
