/*
    ============
    === EASY ===
    ============

    ===============================
    643) Maximum Average Subarray I
    ===============================

    ============
    Description:
    ============

    You are given an integer array nums consisting of n elements, and an
    integer k.

    Find a contiguous subarray whose length is equal to k that has the maximum
    average value and return this value. Any answer with a calculation error
    less than 10-5 will be accepted.

    ==========================================================
    FUNCTION: double findMaxAverage(vector<int>& nums, int k);
    ==========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,12,-5,-6,50,3], k = 4
    Output: 12.75000
    Explanation: Maximum average is (12 - 5 - 6 + 50) / 4 = 51 / 4 = 12.75

    --- Example 2 ---
    Input: nums = [5], k = 1
    Output: 5.00000


    *** Constraints ***
    n == nums.length
    1 <= k <= n <= 105
    -10^4 <= nums[i] <= 10^4

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-Explanatory.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  11.13% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k)
    {
        const int N = nums.size();
        double sum = 0;

        for (int i = 0; i < k; ++i)
            sum += nums[i];

        double max_sum = sum;

        for (int i = k; i < N; ++i)
        {
            sum += nums[i] - nums[i - k];
            max_sum = max(max_sum, sum);
        }

        return max_sum / k;
    }
};
