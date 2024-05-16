#include <iostream>
#include <vector>
#include <queue>

/*
    ============
    === EASY ===
    ============

    ===========================
    414) Third Number Maximum
    ===========================

    ============
    Description:
    ============

    Given an integer array nums, return the third distinct maximum number in
    this array. If the third maximum does not exist, return the maximum number.

    Can you find an O(n) solution?

    ==========================================
    FUNCTION: int thirdMax(vector<int>& nums);
    ==========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [3,2,1]
    Output: 1
    Explanation:
    The first distinct maximum is 3.
    The second distinct maximum is 2.
    The third distinct maximum is 1.

    --- Example 2 ---
    Input: nums = [1,2]
    Output: 2
    Explanation:
    The first distinct maximum is 2.
    The second distinct maximum is 1.
    The third distinct maximum does not exist, so the maximum (2) is returned
    instead.

    --- Example 3 ---
    Input: nums = [2,2,3,1]
    Output: 1
    Explanation:
    The first distinct maximum is 3.
    The second distinct maximum is 2 (both 2's are counted together since they
    have the same value).
    The third distinct maximum is 1.


    *** Constraints ***
    1 <= nums.length <= 10^4
    -2^31 <= nums[i] <= 2^31 - 1

*/

/*
    ------------
    --- IDEA ---
    ------------

    If you know about the Heap data structure, this one should be a breeze.
    If you don't, make sure to learn and then come back.

*/

/* Time  Beats: 50.32% */
/* Space Beats:  5.84% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n) */
class Solution {
public:
    int thirdMax(std::vector<int>& nums)
    {
        if (nums.size() == 1)
            return nums[0];
        else if (nums.size() == 2)
            return std::max(nums[0], nums[1]);

        std::unordered_set<int> uset(nums.begin(), nums.end());
        std::priority_queue<int> heap; // max_heap by default

        for (const int& num : uset)
            heap.push(num);

        if (heap.size() <= 2)
            return heap.top();

        heap.pop();
        heap.pop();

        return heap.top();
    }
};
