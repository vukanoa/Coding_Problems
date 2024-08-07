#include <iostream>

/*
    ============
    === EASY ===
    ============

    ===========================
    896) Monotonic Array
    ===========================

    ============
    Description:
    ============

    An array is monotonic if it is either monotone increasing or monotone
    decreasing.

    An array nums is monotone increasing if for all i <= j, nums[i] <= nums[j].
    An array nums is monotone decreasing if for all i <= j, nums[i] >= nums[j].

    Given an integer array nums, return true if the given array is monotonic,
    or false otherwise.

    ==============================================
    FUNCTION: bool isMonotonic(vector<int>& nums);
    ==============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,2,3]
    Output: true

    --- Example 2 ---
    Input: nums = [6,5,4,4]
    Output: true

    --- Example 3 ---
    Input: nums = [1,3,2]
    Output: false


    *** Constraints ***
    1 <= nums.length <= 10^5
    -10^5 <= nums[i] <= 10^5

*/

/*
    ------------
    --- IDEA ---
    ------------

    This is a naive and messy/awful way to solve this problem. I wanted to
    include it, just so that I can compare how much better it can be solved.

*/

/* Time  Beats: 99.64% */
/* Space Beats: 89.93% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Naive_Messy {
public:
    bool isMonotonic(vector<int>& nums)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates
        
        int type = 0; // 1 => increasing, 2 => decreasing

        for (int i = 1; i < nums.size(); i++)
        {
            if (type > 0)
            {
                if (type == 1)
                {
                    if (nums[i-1] > nums[i])
                        return false;
                }
                else
                {
                    if (nums[i-1] < nums[i])
                        return false;
                }
            }
            else
            {
                if (nums[i-1] == nums[i])
                    continue;

                if (nums[i-1] < nums[i])
                    type = 1;
                else
                    type = 2;
            }
        }

        return true;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Only if both "premises"(i.e. that nums array is strictly increasing or
    strictly decreasing) are disputed, only then can we return "false".

*/

/* Time  Beats: 98.46% */
/* Space Beats: 30.83% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Improved_Naive {
public:
    bool isMonotonic(vector<int>& nums)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates
        
        bool increasing = true;
        bool decreasing = true;

        for (int i = 1; i < nums.size(); i++)
        {
            if (nums[i-1] > nums[i])
                increasing = false;

            if (nums[i-1] < nums[i])
                decreasing = false;
        }

        return increasing || decreasing;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This is a much more elegant approach. It's self-explanatory.

*/

/* Time  Beats: 97.90% */
/* Space Beats: 97.70% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Elegant {
public:
    bool isMonotonic(vector<int>& nums)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates
        
        if (nums[0] > nums.back())
            reverse(nums.begin(), nums.end());

        for (int i = 1; i < nums.size(); i++)
        {
            if (nums[i-1] > nums[i]) // If it's NOT monotonicly INCREASING
                return false;
        }

        return true;
    }
};
