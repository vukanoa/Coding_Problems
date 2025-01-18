/*
    ============
    === EASY ===
    ============

    ======================================================================
    3423) Maximum Difference Between Adjacent Elements in a Circular Array
    ======================================================================

    ============
    Description:
    ============

    Given a circular array nums, find the maximum absolute difference between
    adjacent elements.

    =====
    Note: In a circular array, the first and last elements are adjacent.
    =====

    =====================================================
    FUNCTION: int maxAdjacentDistance(vector<int>& nums);
    =====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,4]
    Output: 3
    Explanation: Because nums is circular, nums[0] and nums[2] are adjacent.
                 They have the maximum absolute difference of |4 - 1| = 3.

    --- Example 2 ---
    Input: nums = [-5,-10,-5]
    Output: 5
    Explanation: The adjacent elements nums[0] and nums[1] have the maximum
                 absolute difference of |-5 - (-10)| = 5.


    *** Constraints ***
    2 <= nums.length <= 100
    -100 <= nums[i] <= 100

*/

#include <cstdlib>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Literally just code it up. Do what you're told.

*/

/* Time  Beats: 100.00% */
/* Space Beats: 100.00% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    int maxAdjacentDistance(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 0;

        result = abs(nums[N-1] - nums[0]);

        for (int i = 0; i < N-1; i ++)
            result = max(result, abs(nums[i] - nums[i+1]));

        return result;
    }
};
