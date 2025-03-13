/*
    ==============
    === MEDIUM ===
    ==============

    ==================================
    3356) Zero Array Transformation II
    ==================================

    ============
    Description:
    ============

    You are given an integer array nums of length n and a 2D array queries
    where queries[i] = [li, ri, vali].

    Each queries[i] represents the following action on nums:

        + Decrement the value at each index in the range [li, ri] in nums by at
          most vali.

        + The amount by which each value is decremented can be chosen
          independently for each index.

    A Zero Array is an array with all its elements equal to 0.

    Return the minimum possible non-negative value of k, such that after
    processing the first k queries in sequence, nums becomes a Zero Array.
    If no such k exists, return -1.

    ============================================================================
    FUNCTION: int minZeroArray(vector<int>& nums, vector<vector<int>>& queries);
    ============================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [2,0,2], queries = [[0,2,1],[0,2,1],[1,1,3]]
    Output: 2
    Explanation:
        For i = 0 (l = 0, r = 2, val = 1):
            Decrement values at indices [0, 1, 2] by [1, 0, 1] respectively.
            The array will become [1, 0, 1].
        For i = 1 (l = 0, r = 2, val = 1):
            Decrement values at indices [0, 1, 2] by [1, 0, 1] respectively.
            The array will become [0, 0, 0], which is a Zero Array. Therefore,
            the minimum value of k is 2.


    --- Example 2 ---
    Input: nums = [4,3,2,1], queries = [[1,3,2],[0,2,1]]
    Output: -1
    Explanation:
        For i = 0 (l = 1, r = 3, val = 2):
            Decrement values at indices [1, 2, 3] by [2, 2, 1] respectively.
            The array will become [4, 1, 0, 0].
        For i = 1 (l = 0, r = 2, val = 1):
            Decrement values at indices [0, 1, 2] by [1, 1, 0] respectively.
            The array will become [3, 0, 0, 0], which is not a Zero Array.


    *** Constraints ***
    1 <= nums.length <= 10^5
    0 <= nums[i] <= 5 * 10^5
    1 <= queries.length <= 10^5
    queries[i].length == 3
    0 <= li <= ri < nums.length
    1 <= vali <= 5

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 66.78% */
/* Space Beats: 63.70% */

/* Time  Complexity: O(logM * (N + M)) */
/* Space Complexity: O(N)              */
class Solution {
public:
    int minZeroArray(vector<int>& nums, vector<vector<int>>& queries)
    {
        const int N = nums.size();
        const int M = queries.size();

        int L = 0;
        int R = M;

        // Zero array isn't formed after all queries are processed
        if ( ! can_form_zero_array(nums, queries, R))
            return -1;

        // Binary Search
        while (L <= R)
        {
            int mid = L + (R - L) / 2;

            if (can_form_zero_array(nums, queries, mid))
                R = mid - 1;
            else
                L = mid + 1;
        }

        // Return earliest query that zero array can be formed
        return L;
    }

private:
    bool can_form_zero_array(vector<int>& nums, vector<vector<int>>& queries, int k)
    {
        const int N = nums.size();
        int sum = 0;

        vector<int> line_sweep(N + 1);

        // Process query
        for (int query_idx = 0; query_idx < k; query_idx++)
        {
            int start = queries[query_idx][0];
            int end   = queries[query_idx][1];
            int val   = queries[query_idx][2];

            // Process start and end of range
            line_sweep[start]   += val;
            line_sweep[end + 1] -= val;
        }

        // Check if zero array can be formed
        for (int i = 0; i < N; i++)
        {
            sum += line_sweep[i];

            if (sum < nums[i])
                return false;
        }

        return true;
    }
};
