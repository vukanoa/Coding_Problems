/*
    ============
    === HARD ===
    ============

    ===============================
    10) Regular Expression Matching
    ===============================

    ============
    Description:
    ============

    Given an input string s and a pattern p, implement regular expression
    matching with support for '.' and '*' where:

        '.' Matches any single character.
        '*' Matches zero or more of the preceding element.

    The matching should cover the entire input string (not partial).

    ===========================================
    FUNCTION: bool isMatch(string s, string p);
    ===========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "aa", p = "a"
    Output: false
    Explanation: "a" does not match the entire string "aa".

    --- Example 2 ---
    Input: s = "aa", p = "a*"
    Output: true
    Explanation: '*' means zero or more of the preceding element, 'a'.
    Therefore, by repeating 'a' once, it becomes "aa".

    --- Example 3 ---
    Input: s = "ab", p = ".*"
    Output: true
    Explanation: ".*" means "zero or more (*) of any character (.)".


    *** Constraints ***
    1 <= s.length <= 20
    1 <= p.length <= 20
    s contains only lowercase English letters.
    p contains only lowercase English letters, '.', and '*'.
    It is guaranteed for each appearance of the character '*', there will be a
    previous valid character to match.

*/

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

/* Time  Beats: 100.00% */
/* Space Beats:  68.03% */

/* Time  Complexity: O(N * M) */
/* Space Complexity: O(N * M) */
class Solution_Top_Down__Memoization {
private:
    int memo[21][21];

public:
    bool isMatch(string s, string p)
    {
        const int N = s.size();
        const int M = p.size();

        /* Memset */
        memset(memo, 0xff, sizeof(memo));

        /* Solve */
        return solve(0, 0, s, p);
    }

private:
    int solve(int i, int j, string& s, string& p)
    {
        const int N = s.size();
        const int M = p.size();

        if (i >= N && j >= M)
            return true;

        if (j >= M)
            return false;

        if (memo[i][j] != -1)
            return memo[i][j];

        int result = false;

        bool match = i < N && (s[i] == p[j] || p[j] == '.');

        if (match)
            result = result | solve(i+1, j+1, s, p);

        if (j+1 < M && p[j+1] == '*')
        {
            result = result | (true  && solve(i  , j+2, s, p)); // Skip
            result = result | (match && solve(i+1, j  , s, p)); // Take
        }

        return memo[i][j] = result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 46.43% */
/* Space Beats: 32.02% */

/* Time  Complexity: O(N * M) */
/* Space Complexity: O(N * M) */
class SolutionR_Bottom_Up__Tabulation {
public:
    bool isMatch(string s, string p)
    {
        const int N = s.size();
        const int M = p.size();

        vector<vector<bool>> dp(N+1, vector<bool>(M+1, false));

        /* Base Case */
        dp[N][M] = true;

        for (int i = N; i >= 0; i--)
        {
            for (int j = M-1; j >= 0; j--)
            {
                bool match = i < N && (s[i] == p[j] || p[j] == '.');

                if (match)
                    dp[i][j] = dp[i][j] | dp[i+1][j+1];

                if (j+1 < M && p[j+1] == '*')
                {
                    dp[i][j] = dp[i][j] | (true  && dp[i  ][j+2]); // Skip
                    dp[i][j] = dp[i][j] | (match && dp[i+1][j  ]); // Take
                }
            }
        }

        return dp[0][0];
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Each state depends only on:

        current row:   dp[i  ][...]
        next    row:   dp[i+1][...]

    Therefore, we can reduce Space Complexity from O(N * M) down to O(M).

*/

/* Time  Beats: 100.00% */
/* Space Beats:  80.94% */

/* Time  Complexity: O(N * M) */
/* Space Complexity: O(M)     */
class Solution_Bottom_Up__Tabulation__Space_Optimized {
public:
    bool isMatch(string s, string p)
    {
        const int N = s.size();
        const int M = p.size();

        vector<bool> next_row(M+1, false);
        next_row[M] = true;

        for (int i = N; i >= 0; i--)
        {
            vector<bool> curr_row(M+1, false);

            /* Base Case */
            if (i == N)
                curr_row[M] = true;

            for (int j = M-1; j >= 0; j--)
            {
                bool match = i < N && (s[i] == p[j] || p[j] == '.');

                if (match)
                    curr_row[j] = curr_row[j] | next_row[j+1];

                if (j+1 < M && p[j+1] == '*')
                {
                    curr_row[j] = curr_row[j] | (true  && curr_row[j+2]); // Skip
                    curr_row[j] = curr_row[j] | (match && next_row[j  ]); // Take
                }
            }

            next_row = std::move(curr_row);
        }

        return next_row[0];
    }
};
