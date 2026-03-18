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

#include <algorithm>
#include <vector>
using namespace std;

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
class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums)
    {
        vector<vector<int>> results; // Don't add initial '{}'
        sort(nums.begin(), nums.end());

        vector<int> subset;
        backtracking(nums, 0, subset, results);

        return results;
    }

private:
    void backtracking(vector<int>& nums,
                      int i,
                      vector<int>& subset,
                      vector<vector<int>>& results)
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




/* Time  Beats: 40.31% */
/* Space Beats: 30.78% */

/* Time  Complexity: O(N * 2^N) */
/* Space Complexity: O(N * 2^N) */
class Solution_Iterative {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums)
    {
        const int N = nums.size();

        // Total number of subsets is up to 2^N, each subset up to size N
        // Space: O(N * 2^N)
        vector<vector<int>> result = {{}};

        sort(nums.begin(), nums.end()); // O(N log N)

        int latest_subsets = 0;

        for (int i = 0; i < N; i++) // Contributes to overall O(N * 2^N)
        {
            vector<vector<int>> new_subsets;

            if (i > 0 && nums[i-1] == nums[i])
            {
                // Only extend subsets created in previous step
                // Number of such subsets is at most 2^N in total across
                // execution
                for (int x = result.size() - latest_subsets; x < result.size(); x++)
                {
                    vector<int> subset = result[x]; // O(N)

                    subset.push_back(nums[i]); // O(1)

                    new_subsets.push_back(subset); // O(N)
                }
            }
            else
            {
                // Iterate over all existing subsets (up to 2^N total)
                for (vector<int> subset : result)
                {
                    subset.push_back(nums[i]); // O(N) (copying subset)

                    new_subsets.push_back(subset); // O(N)
                }
            }

            latest_subsets = new_subsets.size();

            // O(N)
            result.insert(result.end(), new_subsets.begin(), new_subsets.end());
        }

        return result;
    }
};
