#include <iostream>
#include <vector>

/*
    ============
    === EASY ===
    ============

    ===========================
    905) Sort Array By Parity
    ===========================

    ============
    Description:
    ============

    Given an integer array nums, move all the even integers at the beginning of
    the array followed by all the odd integers.

    Return any array that satisfies this condition

    ===========================================================
    FUNCTION: vector<int> sortArrayByParity(vector<int>& nums);
    ===========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [3,1,2,4]
    Output: [2,4,3,1]
    Explanation: The outputs [4,2,3,1], [2,4,1,3], and [4,2,1,3] would also be
                 accepted.

    --- Example 2 ---
    Input: nums = [0]
    Output: [0]


    *** Constraints ***
    1 <= nums.length <= 5000
    0 <= nums[i] <= 5000

*/

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Fundamental Two Pointes approach.

*/

/* Time  Beats: 64.63% */
/* Space Beats: 23.47% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    vector<int> sortArrayByParity(vector<int>& nums)
    {
        int left  = 0;
        int right = 0;

        while (right < nums.size())
        {
            if (nums[right] % 2 == 0) // If nums[right] is an Even number
            {
                swap(nums[left], nums[right]);
                left++;
            }

            right++;
        }

        return nums;
    }
};
