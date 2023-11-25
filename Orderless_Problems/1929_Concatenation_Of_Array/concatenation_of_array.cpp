#include <iostream>

/*
    ============
    === EASY ===
    ============

    ============================
    1929) Concatenation of Array
    ============================

    ============
    Description:
    ============

    Given an integer array nums of length n, you want to create an array ans of
    length 2n where ans[i] == nums[i] and ans[i + n] == nums[i] for 0 <= i < n
    (0-indexed).

    Specifically, ans is the concatenation of two nums arrays.

    Return the array ans.

    ==========================================================
    FUNCTION: vector<int> getConcatenation(vector<int>& nums);
    ==========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,1]
    Output: [1,2,1,1,2,1]
    Explanation: The array ans is formed as follows:
    - ans = [nums[0],nums[1],nums[2],nums[0],nums[1],nums[2]]
    - ans = [1,2,1,1,2,1]


    --- Example 2 ---
    Input: nums = [1,3,2,1]
    Output: [1,3,2,1,1,3,2,1]
    Explanation: The array ans is formed as follows:
    - ans = [nums[0],nums[1],nums[2],nums[3],nums[0],nums[1],nums[2],nums[3]]
    - ans = [1,3,2,1,1,3,2,1]


    *** Constraints ***
    n == nums.length
    1 <= n <= 1000
    1 <= nums[i] <= 1000

*/

/*
    ------------
    --- IDEA ---
    ------------

    Basic use of "std::vector" in C++.

*/

/* Time  Beats: 39.26% */
/* Space Beats: 43.51% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    vector<int> getConcatenation(vector<int>& nums)
    {
        int n = nums.size();

        std::vector<int> ans(n);
        for (int i = 0; i < n; i++)
        {
            ans[i] = nums[i];
            ans.push_back(nums[i]);
        }

        return ans;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    General Approach. This one is also faster.

*/

/* Time  Beats: 94.18% */
/* Space Beats: 60.53% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    vector<int> getConcatenation(vector<int>& nums)
    {
        int n = nums.size();

        std::vector<int> ans(2 * n);
        for (int i = 0; i < n; i++)
            ans[i] = ans[i+n] = nums[i];

        return ans;
    }
};
