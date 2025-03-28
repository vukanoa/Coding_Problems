/*
    ============
    === HARD ===
    ============

    ================================================
    3171) Find Subarray With Bitwise OR Closest to K
    ================================================

    ============
    Description:
    ============

    You are given an array nums and an integer k. You need to find a subarray
    of nums such that the absolute difference between k and the bitwise OR of
    the subarray elements is as small as possible. In other words, select a
    subarray nums[l..r] such that:

            abs(k - (nums[l] OR nums[l + 1] ... OR nums[r]))

    is minimum.

    Return the minimum possible value of the absolute difference.

    A subarray is a contiguous non-empty sequence of elements within an array.

    ==========================================================
    FUNCTION: int minimumDifference(vector<int>& nums, int k);
    ==========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,4,5], k = 3
    Output: 0
    Explanation: The subarray nums[0..1] has OR value 3, which gives the
                 minimum absolute difference |3 - 3| = 0.

    --- Example 2 ---
    Input: nums = [1,3,1,3], k = 2
    Output: 1
    Explanation: The subarray nums[1..1] has OR value 3, which gives the
                 minimum absolute difference |3 - 2| = 1.

    --- Example 3 ---
    Input: nums = [1], k = 10
    Output: 9
    Explanation: There is a single subarray with OR value 1, which gives the minimum
                 absolute difference |10 - 1| = 9.


    *** Constraints ***
    1 <= nums.length <= 10^5
    1 <= nums[i] <= 10^9
    1 <= k <= 10^9

*/

#include <vector>
#include <unordered_set>
#include <climits>
#include <cmath>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 24.36% */
/* Space Beats:  5.77`% */

/* Time  Complexity: O(N * lovV) */
/* Space Complexity: O(N)        */
class Solution {
public:
    int minimumDifference(vector<int>& nums, int k)
    {
        int result = INT_MAX;

        unordered_set<int> prev_OR_values; // Store OR values

        for (int i = 0; i < nums.size(); i++)
        {
            unordered_set<int> new_OR_values;

            // Start with the current element
            new_OR_values.insert(nums[i]);

            // Extend previous OR values with the new element
            for (int val : prev_OR_values)
                new_OR_values.insert(val | nums[i]);

            // Update result with the closest OR to k
            for (int val : new_OR_values)
                result = min(result, abs(k - val));

            // Update OR values for the next iteration
            prev_OR_values = std::move(new_OR_values);
        }

        return result;
    }
};
