/*
    ============
    === EASY ===
    ============

    ================================
    3912) Valid Elements in an Array
    ================================

    ============
    Description:
    ============

    You are given an integer array nums.

    An element nums[i] is considered valid if it satisfies at least one of the
    following conditions:

        + It is strictly greater than every element to its left.
        + It is strictly greater than every element to its right.

    The first and last elements are always valid.

    Return an array of all valid elements in the same order as they appear in
    nums.

    ===========================================================
    FUNCTION: vector<int> findValidElements(vector<int>& nums);
    ===========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,4,2,3,2]
    Output: [1,2,4,3,2]
    Explanation:
        nums[0] and nums[5] are always valid.

        nums[1] and nums[2] are strictly greater than every element to their
                            left.

        nums[4] is strictly greater than every element to its right.
        Thus, the answer is [1, 2, 4, 3, 2].


    --- Example 2 ---
    Input: nums = [5,5,5,5]
    Output: [5,5]
    Explanation:
        The first and last elements are always valid.
        No other elements are strictly greater than all elements to their left
        or to their right.
        Thus, the answer is [5, 5].


    --- Example 3 ---
    Input: nums = [1]
    Output: [1]
    Explanation:
    Since there is only one element, it is always valid. Thus, the answer is
    [1].


    *** Constraints ***
    1 <= nums.length <= 100
    1 <= nums[i] <= 100

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  38.11% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    vector<int> findValidElements(vector<int>& nums)
    {
        const int N = nums.size();
        if (N <= 2)
            return nums;

        vector<int> result;
        result.reserve(N); // To prevent repeated reallocations

        vector<int> prev(N, 0);
        vector<int> next(N, 0);
        prev[0]   = nums[0];
        next[N-1] = nums[N-1];

        for (int i = 1; i < N; i++)
            prev[i] = max(prev[i-1], nums[i]);

        for (int i = N-2; i >= 0; i--)
            next[i] = max(next[i+1], nums[i]);

        result.push_back(nums[0]);
        for (int i = 1; i < N-1; i++)
        {
            if (prev[i-1] < nums[i] || nums[i] > next[i+1])
                result.push_back(nums[i]);
        }
        result.push_back(nums[N-1]);

        return result;
    }
};
