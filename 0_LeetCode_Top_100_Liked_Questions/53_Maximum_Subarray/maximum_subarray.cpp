/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    53) Maximum Subarray
    ===========================

    ============
    Description:
    ============

    Given an integer array "nums", find the subarray which has the largest sum
    and return its sum.

    =============================================
    FUNCTION: int maxSubArray(vector<int>& nums);
    =============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  nums = [-2, 1, -3, 4, -1, 2, 1, -5, 4]
    Output: 6
    Explanation: [4, -1, 2, 1] has the largest sum = 6

    --- Example 2 ---
    Input:  nums = [1]
    Output: 1

    --- Example 3 ---
    Input: nums = [5, 4, -1, 7, 8]
    Output: 23

    *** Constraints ***
    1 <= nums.length <= 10^5
    -10^4 <= nums[i] <= 10^4

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 86.15% */
/* Space Beats: 88.10% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Efficient {
public:
    int maxSubArray(std::vector<int>& nums)
    {
        int dp  = nums[0];
        int max = nums[0];

        for (int i = 1; i < nums.size(); i++)
        {
            dp  = std::max(dp + nums[i], nums[i]);
            max = std::max(max, dp);
        }

        return max;
    }
};
