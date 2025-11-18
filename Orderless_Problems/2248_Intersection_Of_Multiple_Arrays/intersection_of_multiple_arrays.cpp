/*
    ============
    === EASY ===
    ============

    =====================================
    2248) Intersection of Multiple Arrays
    =====================================

    ============
    Description:
    ============

    Given a 2D integer array nums where nums[i] is a non-empty array of
    distinct positive integers, return the list of integers that are present in
    each array of nums sorted in ascending order. 

    ==============================================================
    FUNCTION: vector<int> intersection(vector<vector<int>>& nums);
    ==============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [[3,1,2,4,5],[1,2,3,4],[3,4,5,6]]
    Output: [3,4]
    Explanation: 
    The only integers present in each of nums[0] = [3,1,2,4,5], nums[1] =
    [1,2,3,4], and nums[2] = [3,4,5,6] are 3 and 4, so we return [3,4].

    --- Example 2 ---
    Input: nums = [[1,2,3],[4,5,6]]
    Output: []
    Explanation: 
    There does not exist any integer present both in nums[0] and nums[1], so we
    return an empty list [].


    *** Constraints ***
    1 <= nums.length <= 1000
    1 <= sum(nums[i].length) <= 1000
    1 <= nums[i][j] <= 1000
    All the values of nums[i] are unique.

*/

#include <algorithm>
#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 68.85% */
/* Space Beats: 51.55% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution {
public:
    vector<int> intersection(vector<vector<int>>& nums)
    {
        const int N = nums.size();
        unordered_map<int,int> umap;

        for (const vector<int>& arr : nums)
        {
            for (const auto& elem : arr)
                umap[elem]++;
        }

        vector<int> result;
        for (const auto& entry : umap)
        {
            if (entry.second == N)
                result.push_back(entry.first);
        }

        // O(N * logN)
        sort(result.begin(), result.end());

        return result;
    }
};
