/*
    ============
    === EASY ===
    ============

    =============================================
    1005) Maximize Sum of Array After K Negations
    =============================================

    ============
    Description:
    ============

    Given an integer array nums and an integer k, modify the array in the
    following way:

        + choose an index i and replace nums[i] with -nums[i].

    You should apply this process exactly k times. You may choose the same
    index i multiple times.

    Return the largest possible sum of the array after modifying it in this way

    ==================================================================
    FUNCTION: int largestSumAfterKNegations(vector<int>& nums, int k);
    ==================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [4,2,3], k = 1
    Output: 5
    Explanation: Choose index 1 and nums becomes [4,-2,3].

    --- Example 2 ---
    Input: nums = [3,-1,0,2], k = 3
    Output: 6
    Explanation: Choose indices (1, 2, 2) and nums becomes [3,1,0,2].

    --- Example 3 ---
    Input: nums = [2,-3,-1,5,-4], k = 2
    Output: 13
    Explanation: Choose indices (1, 4) and nums becomes [2,3,-1,5,4].


    *** Constraints ***
    1 <= nums.length <= 10^4
    -100 <= nums[i] <= 100
    1 <= k <= 10^4

*/

#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  59.99% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(1)        */
class Solution {
public:
    int largestSumAfterKNegations(vector<int>& nums, int k)
    {
        const int N = nums.size();

        /* Sort in ASCENDING order */
        sort(nums.begin(), nums.end());

        int i = 0;
        while (i < N && nums[i] < 0 && k > 0)
        {
            nums[i] = -nums[i];

            // Increment, Decrement
            i++;
            k--;
        }

        // If we still have an odd number of flips left, flip the smallest elem
        if (k & 1)
        {
            int idx = min_element(nums.begin(), nums.end()) - nums.begin();
            nums[idx] = -nums[idx];
        }

        return accumulate(nums.begin(), nums.end(), 0);
    }
};
