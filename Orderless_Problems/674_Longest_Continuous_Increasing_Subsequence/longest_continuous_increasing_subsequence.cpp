/*
    ============
    === EASY ===
    ============

    ==============================================
    674) Longest Continuous Increasing Subsequence
    ==============================================

    ============
    Description:
    ============

    Given an unsorted array of integers nums, return the length of the longest
    continuous increasing subsequence (i.e. subarray). The subsequence must be
    strictly increasing.

    A continuous increasing subsequence is defined by two indices l and r
    (l < r) such that it is [nums[l], nums[l + 1], ..., nums[r - 1], nums[r]]
    and for each l <= i < r, nums[i] < nums[i + 1].

    ==================================================
    FUNCTION: int findLengthOfLCIS(vector<int>& nums);
    ==================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,3,5,4,7]
    Output: 3
    Explanation: The longest continuous increasing subsequence is [1,3,5] with
                 length 3. Even though [1,3,5,7] is an increasing subsequence,
                 it is not continuous as elements 5 and 7 are separated by
                 element 4.

    --- Example 2 ---
    Input: nums = [2,2,2,2,2]
    Output: 1
    Explanation: The longest continuous increasing subsequence is [2] with
                 length 1. Note that it must be strictly increasing.


    *** Constraints ***
    1 <= nums.length <= 10^4
    -10^9 <= nums[i] <= 10^9

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Simplest form of "Sliding Window" technique.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  29.81% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int findLengthOfLCIS(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 1;

        int L = 0;
        int R = 1;

        int len_of_curr_subsequence = 1;
        while (R < N)
        {
            if (nums[R-1] < nums[R])
            {
                len_of_curr_subsequence++;
                result = max(result, len_of_curr_subsequence);
            }
            else
            {
                L = R;
                len_of_curr_subsequence = 1; // Reset
            }

            // Increment
            R++;
        }

        return result;
    }
};
