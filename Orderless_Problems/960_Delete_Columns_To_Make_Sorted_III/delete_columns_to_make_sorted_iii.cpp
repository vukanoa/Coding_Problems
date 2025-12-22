/*
    ==============
    === MEDIUM ===
    ==============

    ======================================
    960) Delete Columns to Make Sorted III
    ======================================

    ============
    Description:
    ============

    You are given an array of n strings strs, all of the same length.

    We may choose any deletion indices, and we delete all the characters in
    those indices for each string.

    For example, if we have strs = ["abcdef","uvwxyz"] and deletion indices {0,
    2, 3}, then the final array after deletions is ["bef", "vyz"].

    Suppose we chose a set of deletion indices answer such that after
    deletions, the final array has every string (row) in lexicographic order.
    (i.e., (strs[0][0] <= strs[0][1] <= ... <= strs[0][strs[0].length - 1]),
    and (strs[1][0] <= strs[1][1] <= ... <= strs[1][strs[1].length - 1]), and
    so on). Return the minimum possible value of answer.length.

    ====================================================
    FUNCTION: int minDeletionSize(vector<string>& strs);
    ====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: strs = ["babca","bbazb"]
    Output: 3
    Explanation: After deleting columns 0, 1, and 4, the final array is strs =
                 ["bc", "az"]. Both these rows are individually in
                 lexicographic order (ie. strs[0][0] <= strs[0][1] and
                 strs[1][0] <= strs[1][1]). Note that strs[0] > strs[1] - the
                 array strs is not necessarily in lexicographic order.

    --- Example 2 ---
    Input: strs = ["edcba"]
    Output: 4
    Explanation: If we delete less than 4 columns, the only row will not be
                 lexicographically sorted.

    --- Example 3 ---
    Input: strs = ["ghi","def","abc"]
    Output: 0
    Explanation: All rows are already lexicographically sorted.


    *** Constraints ***
    n == strs.length
    1 <= n <= 100
    1 <= strs[i].length <= 100
    strs[i] consists of lowercase English letters.

*/

#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 57.44% */
/* Space Beats: 92.31% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(N^2) */
class Solution {
public:
    int memo[101][101];

    int N;
    int STRING_LEN;

    int minDeletionSize(vector<string>& strs)
    {
        N   = strs.size();
        STRING_LEN = strs[0].size();

        /* Memset */
        memset(memo, -1, sizeof(memo));

        int longest_non_decreasing_sequence = solve(0, STRING_LEN, strs);

        return STRING_LEN - longest_non_decreasing_sequence;
    }

private:
    int solve(int curr_col_idx, int last_kept_col_idx, vector<string>& strs)
    {
        if (curr_col_idx == STRING_LEN)
            return 0;

        if (memo[curr_col_idx][last_kept_col_idx] != -1)
            return memo[curr_col_idx][last_kept_col_idx];

        bool can_take = true;
        if (last_kept_col_idx != STRING_LEN)
        {
            for (int i = 0; i < N; i++)
            {
                if (strs[i][last_kept_col_idx] > strs[i][curr_col_idx])
                {
                    can_take = false;
                    break;
                }
            }
        }

        // Skip
        int skip = solve(curr_col_idx + 1, last_kept_col_idx, strs);

        // Take
        int take = 0;
        if (can_take)
            take = 1 + solve(curr_col_idx + 1, curr_col_idx, strs);

        return memo[curr_col_idx][last_kept_col_idx] = max(skip, take);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 78.46% */
/* Space Beats: 34.36% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(N)   */
class Solution_Iterative {
public:
    int minDeletionSize(vector<string>& strs)
    {
        const int N          = strs.size();
        const int STRING_LEN = strs[0].size();

        vector<int> dp(STRING_LEN, 1);

        int longest_non_decreasing_sequence = 1;
        for (int curr_col_idx = 0; curr_col_idx < STRING_LEN; curr_col_idx++)
        {
            for (int prev_col_idx = 0; prev_col_idx < curr_col_idx; prev_col_idx++)
            {
                bool can_extend = true;
                for (int i = 0; i < N; i++)
                {
                    if (strs[i][prev_col_idx] > strs[i][curr_col_idx])
                    {
                        can_extend = false;
                        break;
                    }
                }

                if (can_extend)
                    dp[curr_col_idx] = max(dp[curr_col_idx], dp[prev_col_idx] + 1);
            }

            longest_non_decreasing_sequence = max(longest_non_decreasing_sequence, dp[curr_col_idx]);
        }

        return STRING_LEN - longest_non_decreasing_sequence;
    }
};
