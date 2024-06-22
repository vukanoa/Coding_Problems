#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ====================================
    1248) Count Number of Nice Subarrays
    ====================================

    ============
    Description:
    ============

    Given an array of integers nums and an integer k. A continuous subarray is
    called nice if there are k odd numbers on it.

    Return the number of nice sub-arrays.

    ==========================================================
    FUNCTION: int numberOfSubarrays(vector<int>& nums, int k);
    ==========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    <++>

    --- Example 2 ---

    --- Example 3 ---

    *** Constraints ***

*/

/* Time  Beats: 74.98% */
/* Space Beats: 36.89% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_One_Pass {
public:
    int numberOfSubarrays(std::vector<int>& nums, int k)
    {
        int result = 0;
        int count  = 0;

        int left  = 0;
        int right = 0;

        while (right < nums.size())
        {
            if (nums[right] & 1) // If it's odd
            {
                k--;
                count = 0;
            }

            while (k == 0)
            {
                count++;
                k += (nums[left++] & 1); // If it's odd
            }
            result += count;

            right++; // Extend window
        }

        return result;
    }
};
