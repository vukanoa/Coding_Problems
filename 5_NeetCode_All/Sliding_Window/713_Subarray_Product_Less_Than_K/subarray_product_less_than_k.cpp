#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    =================================
    713) Subarray Product Less Than K
    =================================

    ============
    Description:
    ============

    Given an array of integers nums and an integer k, return the number of
    contiguous subarrays where the product of all the elements in the subarray
    is strictly less than k.

    ====================================================================
    FUNCTION: int numSubarrayProductLessThanK(vector<int>& nums, int k);
    ====================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [10,5,2,6], k = 100
    Output: 8
    Explanation: The 8 subarrays that have product less than 100 are:
    [10], [5], [2], [6], [10, 5], [5, 2], [2, 6], [5, 2, 6]
    Note that [10, 5, 2] is not included as the product of 100 is not strictly less than k.

    --- Example 2 ---
    Input: nums = [1,2,3], k = 0
    Output: 0


    *** Constraints ***
    1 <= nums.length <= 3 * 10^4
    1 <= nums[i] <= 1000
    0 <= k <= 10^6

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

    (Fundamental Sliding Window)

*/

/* Time  Beats: 98.33% */
/* Space Beats: 13.11% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k)
    {
        if (k == 0)
            return 0;

        int L = 0;
        int R = 0;

        int result  = 0;
        int product = 1; // Neutral element for Multiplication

        while (R < nums.size())
        {
            product *= nums[R];

            while (L <= R && product >= k)
            {
                product /= nums[L];
                L++;
            }

            result += R - L + 1;
            R++;
        }

        return result;
    }
};
