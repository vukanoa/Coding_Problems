/*
    ==============
    === MEDIUM ===
    ==============

    ==============================================
    712) Minimum ASCII Delete Sum From Two Strings
    ==============================================

    ============
    Description:
    ============

    Given two strings s1 and s2, return the lowest ASCII sum of deleted
    characters to make two strings equal.

    =====================================================
    FUNCTION: int minimumDeleteSum(string s1, string s2);
    =====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s1 = "sea", s2 = "eat"
    Output: 231
    Explanation: Deleting "s" from "sea" adds the ASCII value of "s" (115) to
                 the sum.  Deleting "t" from "eat" adds 116 to the sum.  At the
                 end, both strings are equal, and 115 + 116 = 231 is the
                 minimum sum possible to achieve this.

    --- Example 2 ---
    Input: s1 = "delete", s2 = "leet"
    Output: 403
    Explanation: Deleting "dee" from "delete" to turn the string into "let",
                 adds 100[d] + 101[e] + 101[e] to the sum.  Deleting "e" from
                 "leet" adds 101[e] to the sum.  At the end, both strings are
                 equal to "let", and the answer is 100+101+101+101 = 403.  If
                 instead we turned both strings into "lee" or "eet", we would
                 get answers of 433 or 417, which are higher.


    *** Constraints ***
    1 <= s1.length, s2.length <= 1000
    s1 and s2 consist of lowercase English letters.

*/

#include <climits>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    It's the same technique, but a bit different for the base cases, as in
    "Longest Common Subsequence".

*/

/* Time  Beats: 30.73% */
/* Space Beats: 49.34% */

/* Time  Complexity: O(N * M) */
/* Space Complexity: O(N * M) */
class Solution {
public:
    int minimumDeleteSum(string s1, string s2)
    {
        const int ROWS = s1.size();
        const int COLS = s2.size();

        vector<vector<int>> dp(ROWS+1, vector<int>(COLS+1, INT_MAX));
        dp[ROWS][COLS] = 0; // Base case

        // Initialize Last Row
        for (int row = ROWS-1; row >= 0; row--)
            dp[row][COLS] = s1[row] + dp[row + 1][COLS];

        // Initialize Last Col
        for (int col = COLS-1; col >= 0; col--)
            dp[ROWS][col] = s2[col] + dp[ROWS][col + 1];

        for (int row = ROWS-1; row >= 0; row--)
        {
            for (int col = COLS-1; col >= 0; col--)
            {
                if (s1[row] == s2[col])
                    dp[row][col] = dp[row+1][col+1];
                else
                    dp[row][col] = min( {s1[row]           + dp[row+1][col  ],
                                         s2[col]           + dp[row  ][col+1],
                                         s1[row] + s2[col] + dp[row+1][col+1]} );
            }
        }

        return dp[0][0];
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats:   5.17% */
/* Space Beats: 78.29% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(ROWS * COLS) */
class Solution_Memoization {
private:
    int memo[1001][1001];

public:
    int minimumDeleteSum(string s1, string s2)
    {
        const int ROWS = s1.size();
        const int COLS = s2.size();

        /* Memset */
        memset(memo, 0x7f, sizeof(memo));
        memo[ROWS][COLS] = 0;

        for (int row = ROWS-1; row >= 0; row--)
            memo[row][COLS] = s1[row] + memo[row+1][COLS];

        for (int col = COLS-1; col >= 0; col--)
            memo[ROWS][col] = s2[col] + memo[ROWS][col+1];

        return solve(0, 0, s1, s2);
    }

private:
    int solve(int row, int col, string& s1, string& s2)
    {
        const int ROWS = s1.size();
        const int COLS = s2.size();

        if (memo[row][col] != 0x7f7f7f7f || row >= ROWS || col >= COLS)
            return memo[row][col];

        /* Skip */
        if (s1[row] == s2[col])
            return memo[row][col] = solve(row+1, col+1, s1, s2);

        /* Take */
        int take_s1   = s1[row] +    0    + solve(row+1, col  , s1, s2);
        int take_s2   =    0    + s2[col] + solve(row  , col+1, s1, s2);
        int take_both = s1[row] + s2[col] + solve(row+1, col+1, s1, s2);

        return memo[row][col] = min( {take_s1, take_s2, take_both} );
    }
};
