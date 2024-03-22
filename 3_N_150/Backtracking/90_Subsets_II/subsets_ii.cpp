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

/*
    ------------
    --- IDEA ---
    ------------

    It is very similar to Subset I(first version of this problem), however
    since there are duplicate values in "nums", we must skip them.

    How are we going to do that?

    This is the crux of the Solution:

        while (i != start && i > 0 && i < nums.size() && nums[i-1] == nums[i])
            i++;

*/

/* Time  Beats: 100.00% */
/* Space Beats:  65.72% */

/* Time  Complexity: O(n * 2^n) */
/* Space Complexity: O(n * 2^n) */
class Solution {
public:
    std::vector<std::vector<int>> subsetsWithDup(std::vector<int>& nums)
    {
        std::vector<std::vector<int>> results = {{}};
        std::sort(nums.begin(), nums.end());

        backtracking(nums, 0, {}, results);

        return results;
    }

private:
    void backtracking(std::vector<int>& nums,
                      int start,
                      std::vector<int>& subset,
                      std::vector<std::vector<int>>& results)
    {
        if (start == nums.size())
            return;

        for (int i = start; i < nums.size(); i++)
        {
            while (i != start && i > 0 && i < nums.size() && nums[i-1] == nums[i])
                i++;

            if (i == nums.size())
                return;

            subset.push_back(nums[i]);
            results.push_back(subset);

            backtracking(nums, i+1, subset, results);

            subset.pop_back();
        }
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    A diferent way of implementing the same idea. I'd say this one makes more
    sense, but the above one comes to mind first. At least in my case, since
    that is how I usually write a Batracking Solution.

    Notice that we don't have a "for loop" in this bactracking function.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  65.72% */

/* Time  Complexity: O(n * 2^n) */
/* Space Complexity: O(n * 2^n) */
class Solution_2 {
public:
    std::vector<std::vector<int>> subsetsWithDup(std::vector<int>& nums)
    {
        std::vector<std::vector<int>> results; // Don't add initial '{}'
        std::sort(nums.begin(), nums.end());

        std::vector<int> subset;
        backtracking(nums, 0, subset, results);

        return results;
    }

private:
    void backtracking(std::vector<int>& nums,
                      int i,
                      std::vector<int>& subset,
                      std::vector<std::vector<int>>& results)
    {
        if (i == nums.size())
        {
            results.push_back(subset);
            return;
        }

        // All subsets that do INDEED include nums[i]
        subset.push_back(nums[i]);
        backtracking(nums, i+1, subset, results);
        subset.pop_back();

        // All subsets that do NOT include nums[i]
        while (i+1 < nums.size() && nums[i] == nums[i+1])
            i++;

        backtracking(nums, i+1, subset, results);
    }
};
