/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    47) Permutations II
    ===========================

    ============
    Description:
    ============

    Given a collection of numbers, nums, that might contain duplicates, return
    all possible unique permutations in any order.

    ===============================================================
    FUNCTION: vector<vector<int>> permuteUnique(vector<int>& nums);
    ===============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,1,2]
    Output:[[1,1,2],[1,2,1],[2,1,1]]


    --- Example 2 ---
    Input: nums = [1,2,3]
    Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]


    *** Constraints ***

    1 <= nums.length <= 8
    -10 <= nums[i] <= 10

*/

#include <algorithm>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 69.15% */
/* Space Beats: 80.56% */

/* Time  Complexity: O(N * N!) */
/* Space Complexity: O(N * N!) */
class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums)
    {
        const int N = nums.size();
        vector<vector<int>> results;

        /* Sort */
        sort(nums.begin(), nums.end()); // O(N * logN)

        vector<bool> used(N, false);
        vector<int> curr_permutation;

        /* Backtracking */
        backtracking(curr_permutation, used, results, nums);

        return results;
    }

private:
    void backtracking(vector<int>& curr_permutation, vector<bool>& used, vector<vector<int>>& results, vector<int>& nums)
    {
        if (curr_permutation.size() == nums.size())
        {
            results.push_back(curr_permutation);
            return;
        }

        const int N = nums.size();
        for (int idx = 0; idx < N; idx++)
        {
            if (used[idx] || (idx > 0 && nums[idx - 1] == nums[idx] && ! used[idx - 1]))
                continue;

            curr_permutation.push_back(nums[idx]);
            used[idx] = true;
            backtracking(curr_permutation, used, results, nums);
            used[idx] = false;
            curr_permutation.pop_back();
        }
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 20.21% */
/* Space Beats:  8.58% */

/* Time  Complexity: O(N * N!) */
/* Space Complexity: O(N * N!) */
class Solution_Iterative {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums)
    {
        const int N = nums.size();
        vector<vector<int>> result = {nums};

        /* Sort */
        sort(nums.begin(), nums.end());

        while (true)
        {
            int i = N - 2;

            while (i >= 0 && nums[i] >= nums[i + 1])
                i--;

            if (i < 0)
                break;

            int j = N - 1;
            while (nums[i] >= nums[j])
                j--;

            swap(nums[i], nums[j]);

            /* Reverse */
            reverse(nums.begin() + i + 1, nums.end());

            result.push_back(nums);
        }

        return result;
    }
};
