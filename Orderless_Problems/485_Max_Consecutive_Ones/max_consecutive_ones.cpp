#include <iostream>
#include <vector>

/*
    ============
    === EASY ===
    ============

    ===========================
    485) Max Consecutive Ones
    ===========================

    ============
    Description:
    ============

    Given a binary array nums, return the maximum number of consecutive 1's in
    the array.

    ========================================================
    FUNCTION: int findMaxConsecutiveOnes(vector<int>& nums);
    ========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,1,0,1,1,1]
    Output: 3
    Explanation: The first two digits or the last three digits are consecutive
                 1s. The maximum number of consecutive 1s is 3.


    --- Example 2 ---
    Input: nums = [1,0,1,1,0,1]
    Output: 2


    *** Constraints ***
    1 <= nums.length <= 10^5
    nums[i] is either 0 or 1.

*/

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 54.37% */
/* Space Beats: 14.15% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums)
    {
       int maxi = -1;
       int flag = 0;

       for (auto i : nums)
       {
           if (i == 1)
               flag++;
           else
           {
               maxi = max(maxi, flag);
               flag = 0;
           }
       }

       maxi = max(maxi, flag);

       return maxi;
    }
};
