/*
    ==============
    === MEDIUM ===
    ==============

    ==================================
    3489) Zero Array Transformation IV
    ==================================

    ============
    Description:
    ============

    You are given an integer array nums of length n and a 2D array queries,
    where queries[i] = [li, ri, vali].

    Each queries[i] represents the following action on nums:

        + Select a subset of indices in the range [li, ri] from nums.

        + Decrement the value at each selected index by exactly vali.

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
        For query 0 (l = 0, r = 2, val = 1):
            Decrement the values at indices [0, 2] by 1.
            The array will become [1, 0, 1].
        For query 1 (l = 0, r = 2, val = 1):
            Decrement the values at indices [0, 2] by 1.
            The array will become [0, 0, 0], which is a Zero Array. Therefore,
            the minimum value of k is 2.


    --- Example 2 ---
    Input: nums = [4,3,2,1], queries = [[1,3,2],[0,2,1]]
    Output: -1
    Explanation:
    It is impossible to make nums a Zero Array even after all the queries.


    --- Example 3 ---
    Input: nums = [1,2,3,2,1], queries = [[0,1,1],[1,2,1],[2,3,2],[3,4,1],[4,4,1]]
    Output: 4
    Explanation:
        For query 0 (l = 0, r = 1, val = 1):
            Decrement the values at indices [0, 1] by 1.
            The array will become [0, 1, 3, 2, 1].
        For query 1 (l = 1, r = 2, val = 1):
            Decrement the values at indices [1, 2] by 1.
            The array will become [0, 0, 2, 2, 1].
        For query 2 (l = 2, r = 3, val = 2):
            Decrement the values at indices [2, 3] by 2.
            The array will become [0, 0, 0, 0, 1].
        For query 3 (l = 3, r = 4, val = 1):
            Decrement the value at index 4 by 1.
            The array will become [0, 0, 0, 0, 0]. Therefore, the minimum value of k is 4.


    --- Example 4 ---
    Input: nums = [1,2,3,2,6], queries = [[0,1,1],[0,2,1],[1,4,2],[4,4,4],[3,4,1],[4,4,5]]
    Output: 4


    *** Constraints ***
    1 <= nums.length <= 10
    0 <= nums[i] <= 1000
    1 <= queries.length <= 1000
    queries[i] = [li, ri, vali]
    0 <= li <= ri < nums.length
    1 <= vali <= 10

*/

#include <climits>
#include <iostream>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO
    (This one requires extensive explanation)

*/

/* Time  Beats: 81.28% */
/* Space Beats: 68.56% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    int minZeroArray(vector<int>& nums, vector<vector<int>>& queries)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates

        const int N = nums.size();
        int result = INT_MAX;

        /* Binary Search */
        int L = 0;
        int R = queries.size();

        while (L <= R)
        {
            int mid = L + (R - L) / 2;

            if (can_make_zero_array_with_first_mid_queries(nums, queries, mid))
            {
                R = mid - 1;
                result = min(result, mid);
            }
            else
            {
                L = mid + 1;
            }
        }

        return result == INT_MAX ? -1 : result;
    }

private:
    bool can_make_zero_array_with_first_mid_queries(vector<int>& nums, vector<vector<int>>&queries, int k)
    {
        const int N = nums.size();

        vector<vector<int>> line_sweep(N + 1, vector<int>(11, 0));

        for (int i = 0; i < k; i++)
        {
            int L   = queries[i][0];
            int R   = queries[i][1];
            int val = queries[i][2];

            line_sweep[L][val]++;
            line_sweep[R + 1][val]--;
        }

        vector<int> coins(11, 0);
        for (int i = 0; i < N; i++)
        {
            if (nums[i] == 0)
                continue;

            // Add vector of next Line_sweep index
            for (int x = 0; x < 11; x++)
                coins[x] += line_sweep[i][x];

            if ( ! can_form_target(nums[i], coins))
                return false;
        }

        return true;
    }

    bool can_form_target(int target, vector<int>& coins)
    {
        vector<bool> dp(target + 1, false);
        dp[0] = true;

        for (int i = 0; i < coins.size(); i++)
        {
            if (coins[i] == 0)
                continue;

            for (int t = target; t >= 0; t--)
            {
                for (int c = 1; c <= coins[i] && t >= c * i; c++)
                    dp[t] = dp[t] || dp[t - c * i];
            }
        }

        return dp[target];
    }
};
