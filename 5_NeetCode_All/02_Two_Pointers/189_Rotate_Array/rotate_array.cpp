/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    189) Rotate Array
    ===========================

    ============
    Description:
    ============

    Given an integer array "nums", rotate the array to the right by "k" steps,
    where "k" is non-negative.

    Follow up:
        - Try to come up with as many solution as you can. There are at least
          three different ways to solve this problem.

        - Could you do it in-place with O(1) extra space?

    ================================================
    FUNCTION: void rotate(vector<int>& nums, int k);
    ================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  nums = [1, 2, 3, 4, 5, 6, 7], k = 3
    Output: [5, 6, 7, 1, 2, 3, 4]

    --- Example 2 ---
    Input:  [-1, -100, 3, 99], k = 2
    Output: [3, 99, -1, -100]

    *** Constraints ***
    1 <= nums.length <= 10^5
    -2^31 <= nums[i] <= 2^31 - 1
    0 <= k <= 10^5

*/

#include <algorithm>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    It's not obvious to see this, but once you see it it becomes obvious.
    The code is self-explanatory. Just go through one example.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  41.12% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    void rotate(vector<int>& nums, int k)
    {
        const int N = nums.size();
        k %= N;

        reverse(nums.begin()    , nums.end());
        reverse(nums.begin()    , nums.begin() + k);
        reverse(nums.begin() + k, nums.end());
    }
};
