#include <iostream>
#include <vector>

/*
    ============
    === HARD ===
    ============

    ======================================
    1793) Maximum Score of a Good Subarray
    ======================================

    ============
    Description:
    ============

    You are given an array of integers nums (0-indexed) and an integer k.

    The score of a subarray (i, j) is defined as min(nums[i], nums[i+1], ...,
    nums[j]) * (j - i + 1). A good subarray is a subarray where i <= k <= j.

    Return the maximum possible score of a good subarray.

    =====================================================
    FUNCTION: int maximumScore(vector<int>& nums, int k);
    =====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,4,3,7,4,5], k = 3
    Output: 15
    Explanation: The optimal subarray is (1, 5) with a score of min(4,3,7,4,5)
                 * (5-1+1) = 3 * 5 = 15.

    --- Example 2 ---
    Input: nums = [5,5,4,5,4,1,1,1], k = 0
    Output: 20
    Explanation: The optimal subarray is (0, 4) with a score of min(5,5,4,5,4)
                 * (4-0+1) = 4 * 5 = 20.


    *** Constraints ***
    1 <= nums.length <= 10^5
    1 <= nums[i] <= 2 * 10^4
    0 <= k < nums.length

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 79.08% */
/* Space Beats: 50.14% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    int maximumScore(std::vector<int>& nums, int k)
    {
        int left  = k;
        int right = k;

        int min_val = nums[k];
        int max_score = min_val;

        while (left > 0 || right < nums.size() - 1)
        {
            if (left == 0 || (right < nums.size() - 1 && nums[right + 1] > nums[left - 1]))
                right++;
            else
                left--;

            min_val = std::min(min_val, std::min(nums[left], nums[right]));
            max_score = std::max(max_score, min_val * (right - left + 1));
        }

        return max_score;
    }
};
