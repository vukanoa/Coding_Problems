/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    474) Ones and Zeroes
    ===========================

    ============
    Description:
    ============

    You are given an array of binary strings strs and two integers m and n.

    Return the size of the largest subset of strs such that there are at most m
    0's and n 1's in the subset.

    A set x is a subset of a set y if all elements of x are also elements of y.

    ==============================================================
    FUNCTION: int findMaxForm(vector<string>& strs, int m, int n);
    ==============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: strs = ["10","0001","111001","1","0"], m = 5, n = 3
    Output: 4

    Explanation: The largest subset with at most 5 0's and 3 1's is {"10",
                 "0001", "1", "0"}, so the answer is 4.  Other valid but
                 smaller subsets include {"0001", "1"} and {"10", "1", "0"}.
                 {"111001"} is an invalid subset because it contains 4 1's,
                 greater than the maximum of 3.


    ["0", "1", "00", "01", "011", "010101"] m = 3, n = 6
    Out: 4


    --- Example 2 ---
    Input: strs = ["10","0","1"], m = 1, n = 1
    Output: 2

    Explanation: The largest subset is {"0", "1"}, so the answer is 2.




    *** Constraints ***
    1 <= strs.length <= 600
    1 <= strs[i].length <= 100
    strs[i] consists only of digits '0' and '1'.
    1 <= m, n <= 100

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

    Clasical 1-0 Knapsack Dynamic Programming technique.

    This one is implemented using the Bottom-Up approach.

*/

/* Time  Beats: 73.08% */
/* Space Beats: 96.54% */

/* Time  Complexity: O(SIZE * m * n) */
/* Space Complexity: O(m * n)        */ //More Space efficient than memoization
class Solution_Bottom_Up {
public:
    int findMaxForm(vector<string>& strs, int m, int n)
    {
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));

        for (const auto& bin_str : strs)
        {
            int curr_zeroes = count(bin_str.begin(), bin_str.end(), '0');
            int curr_ones   = bin_str.size() - curr_zeroes;

            for (int i = m; i >= curr_zeroes; i--)
            {
                for (int j = n; j >= (curr_ones); j--)
                {
                    dp[i][j] = max(dp[i][j], 1 + dp[i - curr_zeroes][j - curr_ones]);
                }
            }
        }

        return dp[m][n];
    }
};




/*****************************************************************************/
/******************************** Memoization ********************************/
/*****************************************************************************/
/*
    ------------
    --- IDEA ---
    ------------

    Clasical 1-0 Knapsack Dynamic Programming technique.

    Clean implementation of Memoization.

*/

/* Time  Beats: 56.29% */
/* Space Beats: 59.39% */

/* Time  Complexity: O(SIZE * M * N) */
/* Space Complexity: O(SIZE * M * N) */
class Solution_memo {
private:
    int memo[601][101][101];

public:
    int findMaxForm(vector<string>& strs, int m, int n)
    {
        const int SIZE = strs.size();

        memset(memo, -1, sizeof(memo));

        return solve(0, m, n, strs);
    }

private:
    int solve(int idx, int zeroes, int ones, vector<string>& strs)
    {
        const int SIZE = strs.size();

        if (idx >= SIZE)
            return 0;

        if (memo[idx][zeroes][ones] != -1)
            return memo[idx][zeroes][ones];

        // Skip
        int skip = solve(idx + 1, zeroes, ones, strs);

        // Take
        int take = 0;

        int curr_zeroes = count(strs[idx].begin(), strs[idx].end(), '0');
        int curr_ones   = count(strs[idx].begin(), strs[idx].end(), '1');

        // More efficient, but it's the above is easier to read
        // int curr_ones = strs[idx].size() - curr_zeroes;

        int remaining_zeroes = zeroes - curr_zeroes;
        int remaining_ones   = ones   - curr_ones;

        if (remaining_zeroes >= 0 && remaining_ones >= 0)
            take = 1 + solve(idx + 1, remaining_zeroes, remaining_ones, strs);

        return memo[idx][zeroes][ones] = max(skip, take);
    }
};
