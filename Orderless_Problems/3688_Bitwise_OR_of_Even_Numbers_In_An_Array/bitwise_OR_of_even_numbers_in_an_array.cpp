/*
    ============
    === EASY ===
    ============

    ============================================
    3688) Bitwise OR of Even Numbers in an Array
    ============================================

    ============
    Description:
    ============

    You are given an integer array nums.

    Return the bitwise OR of all even numbers in the array.

    If there are no even numbers in nums, return 0.

    ======================================================
    FUNCTION: int evenNumberBitwiseORs(vector<int>& nums);
    ======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,3,4,5,6]
    Output: 6
    Explanation:
    The even numbers are 2, 4, and 6. Their bitwise OR equals 6.

    --- Example 2 ---
    Input: nums = [7,9,11]
    Output: 0
    Explanation:
    There are no even numbers, so the result is 0.

    --- Example 3 ---
    Input: nums = [1,8,16]
    Output: 24
    Explanation:
    The even numbers are 8 and 16. Their bitwise OR equals 24.


    *** Constraints ***
    1 <= nums.length <= 100
    1 <= nums[i] <= 100

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Simulation problem. Easiest one on the entire LeetCode platform.

*/

/* Time  Beats: 100.00% */
/* Space Beats: 100.00% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int evenNumberBitwiseORs(vector<int>& nums)
    {
        int result = 0;
        for (const int& num : nums)
        {
            if (num & 1)
                continue;

            result |= num;
        }

        return result;
    }
};
