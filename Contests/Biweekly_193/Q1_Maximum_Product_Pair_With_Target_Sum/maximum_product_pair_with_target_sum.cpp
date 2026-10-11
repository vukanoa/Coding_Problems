/*
    ============
    === EASY ===
    ============

    ========================================
    Q1) Maximum Product Pair with Target Sum
    ========================================

    ============
    Description:
    ============

    You are given an integer array nums and an integer target.

    A pair of distinct indices (i, j) is valid if:

        nums[i] + nums[j] == target
        nums[i] > nums[j]

    Return a valid pair [i, j] whose product nums[i] * nums[j] is maximum among
    all valid pairs. If no valid pair exists, return [-1, -1].

    If multiple valid pairs achieve the maximum product, you may return any of
    them.

    =====
    Note: Please do not copy the description during the contest to maintain the
          integrity of your submissions. 
    =====

    ====================================================================
    FUNCTION: vector<int> maxProductPair(vector<int>& nums, int target);
    ====================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,3,4], target = 5
    Output: [2,1]

    --- Example 2 ---
    Input: nums = [-3,-1,4,2], target = 1
    Output: [3,1]

    --- Example 3 ---
    Input: nums = [3,3,5], target = 6
    Output: [-1,-1]


    *** Constraints ***
    2 <= nums.length <= 100
    -100 <= nums[i], target <= 100

*/

#include <climits>
#include <vector>
using namespace std;

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    vector<int> maxProductPair(vector<int>& nums, int target)
    {
        const int N = nums.size();
        vector<int> result = {-1, -1};
        int product = INT_MIN;
        
        for (int i = 0; i < N; i++)
        {
            for (int j = i+1; j < N; j++)
            {
                if (nums[i] + nums[j] == target && nums[i] * nums[j] > product)
                {
                    if (nums[i] == nums[j])
                        continue;
                    
                    if (nums[i] > nums[j])
                        result = {i, j};
                    else
                        result = {j, i};
                    
                    product = nums[i] * nums[j];
                }
            }
        }

        return result;
    }
};
