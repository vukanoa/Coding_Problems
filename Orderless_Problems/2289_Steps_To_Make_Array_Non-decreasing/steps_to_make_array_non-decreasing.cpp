/*
    ==============
    === MEDIUM ===
    ==============

    ===========================================
    2289) Steps to Make an Array Non-decreasing
    ===========================================

    ============
    Description:
    ============

    You are given a 0-indexed integer array nums. In one step, remove all
    elements nums[i] where nums[i - 1] > nums[i] for all 0 < i < nums.length.

    Return the number of steps performed until nums becomes a non-decreasing
    array.

    ============================================
    FUNCTION: int totalSteps(vector<int>& nums);  
    ============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [5,3,4,4,7,3,6,11,8,5,11]
    Output: 3
    Explanation: The following are the steps performed:
    - Step 1: [5,3,4,4,7,3,6,11,8,5,11] becomes [5,4,4,7,6,11,11]
    - Step 2: [5,4,4,7,6,11,11] becomes [5,4,7,11,11]
    - Step 3: [5,4,7,11,11] becomes [5,7,11,11]
    [5,7,11,11] is a non-decreasing array. Therefore, we return 3.

    --- Example 2 ---
    Input: nums = [4,5,7,7,13]
    Output: 0
    Explanation: nums is already a non-decreasing array. Therefore, we return 0


    *** Constraints ***
    1 <= nums.length <= 10^5
    1 <= nums[i] <= 10^9

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 94.52% */
/* Space Beats: 10.66% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    int totalSteps(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 0;

        vector<int> stack;
        vector<int> dp(N);
        for (int i = N-1; i >= 0; i--)
        {
            while ( ! stack.empty() && nums[i] > nums[stack.back()])
            {
                dp[i] = max(++dp[i], dp[stack.back()]);
                stack.pop_back();
                result = max(result, dp[i]);
            }

            stack.push_back(i);
        }

        return result;
    }
};
