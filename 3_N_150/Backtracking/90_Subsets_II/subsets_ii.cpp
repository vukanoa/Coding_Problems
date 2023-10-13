#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    90) Subsets II
    ===========================

    ============
    Description:
    ============

    Given an integer array nums that may contain duplicates, return all
    possible subsets (the power set).

    The solution set must not contain duplicate subsets. Return the solution in
    any order.

    ==============================================================
    FUNCTION: vector<vector<int> subsetWithDup(vector<int>& nums);
    ==============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,2]
    Output: [[],[1],[1,2],[1,2,2],[2],[2,2]]

    --- Example 2 ---
    Input: nums = [0]
    Output: [[],[0]]

    *** Constraints ***
    1 <= nums.length <= 10
    -10 <= nums[i] <= 10


    nums  = [1, 2, 3]
    Out: [[], [1], [1, 2], [1, 2, 3], [1, 3], [2], [2, 3], [3]]

*/

/*
    ------------
    --- IDEA ---
    ------------

    Very similar to:
    1. "Subsets" (First version of this problem)
    2. "Permutations" problem, or
    3. "Combination Sum", or
    4. "Combination Sum II"

*/

/* Time  Beats:  100% */
/* Space Beats: 59.34% */

/* Time  Complexity: O(n * 2^n) */
/* Space Complexity: O(n * 2^n) */
class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums)
    {
        std::vector<std::vector<int>> results = {{}};
        std::sort(nums.begin(), nums.end());

        std::vector<int> curr_combination;
        backtracking(nums, 0, curr_combination, results);

        return results;
    }

private:
    void backtracking(std::vector<int>& nums, int start, std::vector<int>& curr_combination, std::vector<std::vector<int>>& results)
    {
        if (start == nums.size())
            return;

        for (int i = start; i < nums.size(); i++)
        {
            while (i != start && i > 0 && i < nums.size() && nums[i-1] == nums[i])
                i++;

            if (i == nums.size())
                return;

            curr_combination.push_back(nums[i]);
            results.push_back(curr_combination);

            backtracking(nums, i+1, curr_combination, results);

            curr_combination.pop_back();
        }
    }
};
