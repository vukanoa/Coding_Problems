/*
    ==============
    === MEDIUM ===
    ==============

    =====================================================
    3381) Maximum Subarray Sum With Length Divisible By K
    =====================================================

    ============
    Description:
    ============

    You are given an array of integers nums and an integer k.

    Return the maximum sum of a subarray of nums, such that the size of the
    subarray is divisible by k.

    =============================================================
    FUNCTION: long long maxSubarraySum(vector<int>& nums, int k);
    =============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2], k = 1
    Output: 3
    Explanation: The subarray [1, 2] with sum 3 has length equal to 2 which is
                 divisible by 1.

    --- Example 2 ---
    Input: nums = [-1,-2,-3,-4,-5], k = 4
    Output: -10
    Explanation: The maximum sum subarray is [-1, -2, -3, -4] which has length
                 equal to 4 which is divisible by 4.

    --- Example 3 ---
    Input: nums = [-5,1,2,-3,4], k = 2
    Output: 4
    Explanation: The maximum sum subarray is [1, 2, -3, 4] which has length
                 equal to 4 which is divisible by 2.


    *** Constraints ***
    1 <= k <= nums.length <= 2 * 10^5
    -10^9 <= nums[i] <= 10^9

*/

#include <climits>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 42.28% */
/* Space Beats: 98.32% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(k) */
class Solution {
public:
    long long maxSubarraySum(vector<int>& nums, int k)
    {
        const int N = nums.size();
        long long result = LLONG_MIN;

        vector<long long> min_remainder(k, LLONG_MAX);
        min_remainder[0] = 0;

        long long sum = 0LL;
        for (int i = 0; i < N; i++)
        {
            sum += nums[i];
            int rem = (i + 1) % k;

            if (min_remainder[rem] != LLONG_MAX)
                result = max(result, sum - min_remainder[rem]);

            min_remainder[rem] = min(min_remainder[rem], sum);
        }

        return result;
    }
};
