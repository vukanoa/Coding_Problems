/*
    ============
    === EASY ===
    ============

    ====================================
    3718) Smallest Missing Multiple of K
    ====================================

    ============
    Description:
    ============

    Given an integer array nums and an integer k, return the smallest positive
    multiple of k that is missing from nums.

    A multiple of k is any positive integer divisible by k.

    ========================================================
    FUNCTION: int missingMultiple(vector<int>& nums, int k);
    ========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [8,2,3,4,6], k = 2
    Output: 10
    Explanation:
    The multiples of k = 2 are 2, 4, 6, 8, 10, 12... and the smallest multiple
    missing from nums is 10.

    --- Example 2 ---
    Input: nums = [1,4,7,10,15], k = 5
    Output: 5
    Explanation:
    The multiples of k = 5 are 5, 10, 15, 20... and the smallest multiple
    missing from nums is 5.


    *** Constraints ***
    1 <= nums.length <= 100
    1 <= nums[i] <= 100
    1 <= k <= 100

*/

#include <unordered_set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats:  9.55% */
/* Space Beats: 45.06% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    int missingMultiple(vector<int>& nums, int k)
    {
        unordered_set<int> uset(nums.begin(), nums.end());

        int multiple = k;
        while (uset.count(multiple))
        {
            multiple += k;
        }

        return multiple;
    }
};
