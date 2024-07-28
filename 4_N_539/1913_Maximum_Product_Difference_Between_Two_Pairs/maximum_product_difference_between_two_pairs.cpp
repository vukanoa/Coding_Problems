#include <iostream>
#include <vector>

/*
    ============
    === EASY ===
    ============

    ==================================================
    1913) Maximum Product Difference Between Two Pairs
    ==================================================

    ============
    Description:
    ============

    The product difference between two pairs (a, b) and (c, d) is defined as
        (a * b) - (c * d).

        For example, the product difference between (5, 6) and (2, 7) is
            (5 * 6) - (2 * 7) = 16.

    Given an integer array nums, choose four distinct indices w, x, y, and z
    such that the product difference between pairs (nums[w], nums[x]) and
    (nums[y], nums[z]) is maximized.

    Return the maximum such product difference.

    ======================================================
    FUNCTION: int maxProductDifference(vector<int>& nums);
    ======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [5,6,2,7,4]
    Output: 34
    Explanation: We can choose indices 1 and 3 for the first pair (6, 7) and
    indices 2 and 4 for the second pair (2, 4).  The product difference is (6 *
    7) - (2 * 4) = 34.

    --- Example 2 ---
    Input: nums = [4,2,5,9,7,4,8]
    Output: 64
    Explanation: We can choose indices 3 and 6 for the first pair (9, 8) and
    indices 1 and 5 for the second pair (2, 4).  The product difference is (9 *
    8) - (2 * 4) = 64.


    *** Constraints ***
    4 <= nums.length <= 10^4
    1 <= nums[i] <= 10^4

*/

/*
    ------------
    --- IDEA ---
    ------------

    Intuitive.

*/

/* Time  Beats: 83.72% */
/* Space Beats: 74.01% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    int maxProductDifference(vector<int>& nums)
    {
        int first_largest  = -1;
        int second_largest = -1;

        int first_smallest  = INT_MAX;
        int second_smallest = INT_MAX;

        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] > first_largest)
            {
                second_largest = first_largest;
                first_largest = nums[i];
            }
            else if (nums[i] > second_largest)
            {
                second_largest = nums[i];
            }

            if (nums[i] < first_smallest)
            {
                second_smallest = first_smallest;
                first_smallest  = nums[i];
            }
            else if (nums[i] < second_smallest)
            {
                second_smallest = nums[i];
            }
        }

        return (first_largest * second_largest) - (first_smallest * second_smallest);
    }
};
