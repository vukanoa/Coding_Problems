/*
    ==============
    === MEDIUM ===
    ==============

    ==============================
    209) Minimum Size Subarray Sum
    ==============================

    ============
    Description:
    ============

    Given an array of positive integers nums and a positive integer target,
    return the minimal length of a subarray whose sum is greater than or equal
    to target. If there is no such subarray, return 0 instead.

    ============================================================
    FUNCTION: int minSubarrayLen(int target, vector<int>& nums);
    ============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: target = 7, nums = [2,3,1,2,4,3]
    Output: 2
    Explanation: The subarray [4,3] has the minimal length under the problem
                 constraint.

    --- Example 2 ---
    Input: target = 4, nums = [1,4,4]
    Output: 1

    --- Example 3 ---
    Input: target = 11, nums = [1,1,1,1,1,1,1,1]
    Output: 0

    *** Constraints ***
    1 <= target <= 10^9
    1 <= nums.length <= 10^5
    1 <= nums[i] <= 10^4

*/

#include <algorithm>
#include <climits>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    This is THE most fundamental non-Fixed(Dynamic) Sliding Window problem
    there is.

    Even the name of the problem says "Subarray" and hints you even more that
    it's a Sliding Window kind of problem.

    If you've never seen a Sliding Window problem, you may mistakenly think
    that two for loops mean this is a O(n^2) Time Complexity Solution, however
    when you understand what's happening, you'll quickly realize we don't
    iterate over any element more than twice. In fact, we cannot iterate
    through elements more than twice, that is the upper bound.

    Therefore, the Time Complexity is not O(n^2), but O(2 * n) which is just:
    O(n) since constants are neglected in Big O notation.


    The most fundamental non-Fixed(Dynamic) Sliding Window technqiue:

        Expand the window by moving the 'R' pointer to the right until the
        elements in window [L, R] become greater than or equal to target.

        Once the sum of window becomes greater than or equal to target, then in
        nested for loop, we do:
            1. Check if the current window_len(i.e. R-L+1) is the new minimum
            window_len that gives us a sum that is greater than or equal to
            "target" and update if it is.

            2. Shrink the window from the left side and, thus, subtract the
               leftmost element of the current window from the sum of the
               current window and move the left boundary to the right by one,
               i.e. increment 'L' pointer.

        Once the while loop ends, we increment the 'R' pointer.

        At the very end we must check if our "result" variable has stayed the
        same, i.e. INT_MAX. If that happened that means that the total sum of
        the array is not enough to be greater than or equal to "target" which
        further means, as we're told in the Description, we should return 0.

        Otherwise return the minimum window_len(i.e. R - L + 1) we've found
        while performing this Sliding-Window technique.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  39.77% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums)
    {
        const int N = nums.size();
        int result = INT_MAX;

        int sum = 0;

        int L = 0;
        int R = 0;
        while (R < N)
        {
            sum += nums[R];

            while (sum >= target)
            {
                result = min(result, R - L + 1);

                // Shrink the Window
                sum -= nums[L];
                L++;
            }

            // Increment
            R++;
        }

        return result == INT_MAX ? 0 : result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    A "Follow Up" asks us to solve this in a LESS EFFICIENT way. So here it is.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  6.63% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution_Follow_Up {
public:
    int minSubArrayLen(int target, vector<int>& nums)
    {
        const int N = nums.size();
        int result = INT_MAX;

        vector<int> prefix_sum(N, 0);
        prefix_sum[N-1] = nums[N-1];

        // O(N) (entire block)
        for (int i = N-2; i >= 0; i--)
            prefix_sum[i] = nums[i] + prefix_sum[i+1];

        // O(N * logN)
        for (int left = 0; left < N; left++)
        {
            if (prefix_sum[left] < target)
                break;

            // O(log N)
            auto iter = upper_bound(prefix_sum.rbegin(), prefix_sum.rend(), prefix_sum[left] - target);
            int right = prefix_sum.rend() - iter - 1;

            result = min(result, right - left + 1);
        }

        return result == INT_MAX ? 0 : result;
    }
};
