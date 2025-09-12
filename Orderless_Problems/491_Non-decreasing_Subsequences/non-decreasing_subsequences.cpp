/*
    ==============
    === MEDIUM ===
    ==============

    ================================
    491) Non-decreasing Subsequences
    ================================

    ============
    Description:
    ============

    Given an integer array nums, return all the different possible
    non-decreasing subsequences of the given array with at least two elements.

    You may return the answer in any order.

    ==================================================================
    FUNCTION: vector<vector<int>> findSubsequences(vector<int>& nums);
    ==================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [4,6,7,7]
    Output: [[4,6],[4,6,7],[4,6,7,7],[4,7],[4,7,7],[6,7],[6,7,7],[7,7]]

    --- Example 2 ---
    Input: nums = [4,4,3,2,1]
    Output: [[4,4]]


    *** Constraints ***
    1 <= nums.length <= 15
    -100 <= nums[i] <= 100

*/

#include <set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Classic Backtracking problem.

*/

/* Time  Beats: 68.30% */
/* Space Beats: 88.81% */

/* Time  Complexity: O(2^N * N * logM) */ // Where 'M' is num of UNIQUE subseqs
/* Space Complexity: O(2^N * N)        */
class Solution {
public:
    vector<vector<int>> findSubsequences(vector<int>& nums)
    {
        set<vector<int>> result;

        vector<int> curr;
        backtracking(0, curr, nums, result);

        return vector(result.begin(), result.end());

    }

private:
    void backtracking(int idx, vector<int>& curr, vector<int>& nums, set<vector<int>>& result)
    {
        const int N = nums.size();

        if (idx >= N)
        {
            if (curr.size() >= 2)
                result.insert(curr);

            return;
        }

        if ( ! curr.size() || nums[idx] >= curr.back())
        {
            curr.push_back(nums[idx]);
            backtracking(idx+1, curr, nums, result);
            curr.pop_back();
        }

        backtracking(idx+1, curr, nums, result);
    }
};
