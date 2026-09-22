/*
    ==============
    === MEDIUM ===
    ==============

    =====================================================
    4058) Maximum Pulse Value After One Subarray Rotation
    =====================================================

    ============
    Description:
    ============

    You are given an integer array nums of length n.

    Define the pulse value of an integer array arr as the alternating sum
    starting at index 0: pulse(arr) = arr[0] - arr[1] + arr[2] - arr[3] + ....

    You may perform at most one operation on nums:

        + Choose two indices l and r such that 0 <= l < r < n.

        + Left-rotate the nums[l..r] by exactly one position. For example, [a,
          b, c, d] becomes [b, c, d, a].


    Return the maximum pulse value that can be obtained after performing at
    most one such operation.

    ================================================
    FUNCTION: long long maxValue(vector<int>& nums);
    ================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,5,2]
    Output: 6
    Explanation:
        The original pulse value is 1 - 5 + 2 = -2.
        Rotate the subarray nums[0..1] from [1, 5] to [5, 1].
        The resulting array is [5, 1, 2] and its pulse value is 5 - 1 + 2 = 6,
        which is the maximum possible.

    --- Example 2 ---
    Input: nums = [6,4,3]
    Output: 7
    Explanation:
        The original pulse value is 6 - 4 + 3 = 5.
        Rotate the subarray nums[1..2] from [4, 3] to [3, 4].
        The resulting array is [6, 3, 4] and its pulse value is 6 - 3 + 4 = 7,
        which is the maximum possible.

    --- Example 3 ---
    Input: nums = [9,7]
    Output: 2
    Explanation:
    The original pulse value is 9 - 7 = 2, which is already maximum. Thus, no
    rotation is required.


    *** Constraints ***
    1 <= n == nums.length <= 10^5
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

/* Time  Beats: 100.00% */
/* Space Beats:  65.80% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    long long maxValue(vector<int>& nums)
    {
        const int N = nums.size();

        long long original_pulse     = 0;
        long long min_subarray_pulse = INT_MAX;

        long long max_even_len_prefix_sum = 0;
        long long max_odd_len_prefix_sum  = INT_MIN;

        for (int i = 0; i < N; i++)
        {
            // Alternating prefix sum
            original_pulse += (i % 2 == 0 ? nums[i] : -nums[i]);

            // (i+1) is the LENGTH of the CURRENT SUBARRAY because indices are 0-based
            if ((i + 1) % 2 == 0) // Current subarray is of EVEN length
            {
                min_subarray_pulse      = min(min_subarray_pulse     , original_pulse - max_even_len_prefix_sum);
                max_even_len_prefix_sum = max(max_even_len_prefix_sum, original_pulse                          );
            }
            else // Current subarray is of ODD length
            {
                min_subarray_pulse     = min(min_subarray_pulse    , original_pulse - max_odd_len_prefix_sum);
                max_odd_len_prefix_sum = max(max_odd_len_prefix_sum, original_pulse                         );
            }
        }

        // Apply THE BEST possible improvement (possibly NONE, i.e. 0)
        return original_pulse - 2 * min(0LL, min_subarray_pulse);
    }
};
