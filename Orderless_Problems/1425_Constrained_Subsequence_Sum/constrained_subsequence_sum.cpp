#include <iostream>
#include <vector>
#include <queue>

/*
    ============
    === HARD ===
    ============

    =================================
    1425) Constrained Subsequence Sum
    =================================

    ============
    Description:
    ============

    Given an integer array nums and an integer k, return the maximum sum of a
    non-empty subsequence of that array such that for every two consecutive
    integers in the subsequence, nums[i] and nums[j], where i < j, the
    condition j - i <= k is satisfied.

    A subsequence of an array is obtained by deleting some number of elements
    (can be zero) from the array, leaving the remaining elements in their
    original order.

    =============================================================
    FUNCTION: int constrainedSubsetSum(vector<int>& nums, int k);
    =============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [10,2,-10,5,20], k = 2
    Output: 37
    Explanation: The subsequence is [10, 2, 5, 20].


    --- Example 2 ---
    Input: nums = [-1,-2,-3], k = 1
    Output: -1
    Explanation: The subsequence must be non-empty, so we choose the largest
                 number.


    --- Example 3 ---
    Input: nums = [10,-2,-10,-5,20], k = 2
    Output: 23
    Explanation: The subsequence is [10, -2, -5, 20].


    *** Constraints ***
    1 <= k <= nums.length <= 10^5
    -10^4 <= nums[i] <= 10^4

*/

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 70.17% */
/* Space Beats: 92.27% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(k) */
class Solution {
public:
    int constrainedSubsetSum(vector<int>& nums, int k)
    {
        int max_sum = nums[0];
        deque<int> max_sum_queue;

        for (int i = 0; i < nums.size(); i++)
        {
            nums[i] += !max_sum_queue.empty() ? max_sum_queue.front() : 0;
            max_sum = max(max_sum, nums[i]);

            while (!max_sum_queue.empty() && nums[i] > max_sum_queue.back())
                max_sum_queue.pop_back();

            if (nums[i] > 0)
                max_sum_queue.push_back(nums[i]);

            if (i >= k && !max_sum_queue.empty() && max_sum_queue.front() == nums[i - k])
                max_sum_queue.pop_front();
        }

        return max_sum;
    }
};
