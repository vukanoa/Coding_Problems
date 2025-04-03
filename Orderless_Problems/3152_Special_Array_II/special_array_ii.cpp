/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    3152) Special Array II
    ===========================

    ============
    Description:
    ============

    An array is considered special if every pair of its adjacent elements contains two numbers with different parity.

    You are given an array of integer nums and a 2D integer matrix queries, where for queries[i] = [fromi, toi] your task is to check that
    subarray
    nums[fromi..toi] is special or not.

    Return an array of booleans answer such that answer[i] is true if nums[fromi..toi] is special.

    =======================================================================================
    FUNCTION: vector<bool> isArraySpecial(vector<int>& nums, vector<vector<int>>& queries);
    =======================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [3,4,1,2,6], queries = [[0,4]]
    Output: [false]
    Explanation:
    The subarray is [3,4,1,2,6]. 2 and 6 are both even.

    --- Example 2 ---
    Input: nums = [4,3,1,6], queries = [[0,2],[2,3]]
    Output: [false,true]
    Explanation:
        The subarray is [4,3,1]. 3 and 1 are both odd. So the answer to this
        query is false.
        The subarray is [1,6]. There is only one pair: (1,6) and it contains
        numbers with different parity. So the answer to this query is true.


    *** Constraints ***
    1 <= nums.length <= 10^5
    1 <= nums[i] <= 10^5
    1 <= queries.length <= 10^5
    queries[i].length == 2
    0 <= queries[i][0] <= queries[i][1] <= nums.length - 1

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

/* Time  Beats: 41.14% */
/* Space Beats: 95.80% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution_Binary_Search {
public:
    vector<bool> isArraySpecial(vector<int>& nums, vector<vector<int>>& queries)
    {
        const int N = nums.size();
        const int M = queries.size();

        vector<bool> answer(M);

        vector<bool> vec(N, false);
        vec[0] = true;

        vector<int> range;
        for (int i = 1; i < N; i++)
        {
            if (nums[i] & 1)
            {
                if (nums[i-1] & 1)
                {
                    vec[i] = false;
                    range.push_back(i);
                }
                else
                    vec[i] = true;
            }
            else
            {
                if ( ! (nums[i-1] & 1))
                {
                    vec[i] = false;
                    range.push_back(i);
                }
                else
                    vec[i] = true;
            }
        }

        /* Sort */
        sort(range.begin(), range.end()); // O(N * logN)

        for (int q = 0; q < M; q++)
        {
            int start = queries[q][0];
            int end   = queries[q][1];

            // O(logn)
            auto iter = upper_bound(range.begin(), range.end(), start);

            if (iter == range.end())
                answer[q] = true;
            else
            {
                if (*iter > end)
                    answer[q] = true;
                else
                    answer[q] = false;
            }
        }

        return answer;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 87.50% */
/* Space Beats: 51.45% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    vector<bool> isArraySpecial(vector<int>& nums, vector<vector<int>>& queries)
    {
        const int N = nums.size();
        const int M = queries.size();

        vector<bool> answer;

        vector<pair<bool,int>> dp(N, {true, N});
        for (int i = N-2; i >= 0; i--)
        {
            if (
                (nums[i] % 2 == 0 && nums[i+1] % 2 == 1)
                ||
                (nums[i] % 2 == 1 && nums[i+1] % 2 == 0)
               )
            {
                dp[i] = {true, dp[i+1].second};
            }
            else
            {
                dp[i] = {false, i};
            }
        }

        for (const vector<int> &q: queries)
        {
            const int& from = q[0];
            const int& to   = q[1];

            if (from == to)
            {
                answer.push_back(true);
                continue;
            }

            if (dp[from].first && dp[to-1].first && dp[from].second > to-1 && dp[to-1].second > to-1)
                answer.push_back(true);
            else
                answer.push_back(false);
        }

        return answer;
    }
};
