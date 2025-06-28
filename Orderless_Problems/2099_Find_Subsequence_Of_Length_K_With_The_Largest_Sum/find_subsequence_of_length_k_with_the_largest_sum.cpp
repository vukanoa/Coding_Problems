/*
    ============
    === EASY ===
    ============

    =======================================================
    2099) Find Subsequence of Length K With the Largest Sum
    =======================================================

    ============
    Description:
    ============

    You are given an integer array nums and an integer k. You want to find a
    subsequence of nums of length k that has the largest sum.

    Return any such subsequence as an integer array of length k.

    A subsequence is an array that can be derived from another array by
    deleting some or no elements without changing the order of the remaining
    elements.

    ===============================================================
    FUNCTION: vector<int> maxSubsequence(vector<int>& nums, int k);
    ===============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [2,1,3,3], k = 2
    Output: [3,3]
    Explanation:
    The subsequence has the largest sum of 3 + 3 = 6.

    --- Example 2 ---
    Input: nums = [-1,-2,3,4], k = 3
    Output: [-1,3,4]
    Explanation:
    The subsequence has the largest sum of -1 + 3 + 4 = 6.

    --- Example 3 ---
    Input: nums = [3,4,3,3], k = 2
    Output: [3,4]
    Explanation:
    The subsequence has the largest sum of 3 + 4 = 7.
    Another possible subsequence is [4, 3].


    *** Constraints ***
    1 <= nums.length <= 1000
    -10^5 <= nums[i] <= 10^5
    1 <= k <= nums.length

*/

#include <algorithm>
#include <vector>
using namespace std;
#include <algorithm>

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 7.68% */
/* Space Beats: 6.40% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution {
private:
    static bool compare_by_value_desc(const pair<int, int>& a, const pair<int, int>& b)
    {
        return a.second > b.second;
    }

    static bool compare_by_index_asc(const pair<int, int>& a, const pair<int, int>& b)
    {
        return a.first < b.first;
    }

public:
    vector<int> maxSubsequence(vector<int>& nums, int k)
    {
        const int N = nums.size();
        vector<pair<int, int>> value_index_pairs;

        for (int i = 0; i < N; i++)
            value_index_pairs.emplace_back(i, nums[i]);

        sort(value_index_pairs.begin(), value_index_pairs.end()      , compare_by_value_desc);
        sort(value_index_pairs.begin(), value_index_pairs.begin() + k, compare_by_index_asc);

        vector<int> result;
        for (int i = 0; i < k; i++)
            result.push_back(value_index_pairs[i].second);

        return result;
    }
};
