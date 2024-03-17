#include <iostream>

/*
    ==============
    === MEDIUM ===
    ==============

    ==================================
    280) Wiggle Sort (Premium problem)
    ==================================

    ============
    Description:
    ============

    Given an unsorted arrat nums, reorder it in-place such that:
        nums[0] <= nums[1] >= nums[2] <= nums[3] ...

    =============================================
    FUNCTION: void wiggleSort(vector<int>& nums);
    =============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  [3, 5, 2, 1, 6, 4]
    Output: [1, 6, 2, 5, 3, 4]
    Explanation: This quesiton may have multiple answers, such as:
        [2, 6, 1, 5, 3, 4]


    *** Constraints ***
    <Unknown>

*/

/*
    ------------
    --- IDEA ---
    ------------

    Obviously this can be written in a more concise way, but this is way more
    readable.

    This isn't too messy, so I'm going to leave it like that.

*/

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution{
public:
    void wiggleSort(std::vector<int>& nums)
    {
        for (int i = 1; i < nums.size(); i++)
        {
            if (i & 1) // Odd indices
            {
                if (nums[i-1] > nums[i])
                    std::swap(nums[i-1], nums[i]);
            }
            else // Even indices
            {
                if (nums[i-1] < nums[i])
                    std::swap(nums[i-1], nums[i]);
            }
        }
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Equivalent IDEA, written in concise way.

*/

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Concise {
public:
    void wiggleSort(std::vector<int>& nums)
    {
        for (int i = 1; i < nums.size(); i++)
        {
            if ((i % 2 == 1 && nums[i-1] > nums[i]) || // Odd  indices
                (i % 2 == 0 && nums[i-1] < nums[i]))   // Even indices
                std::swap(nums[i-1], nums[i]);
        }
    }
};
