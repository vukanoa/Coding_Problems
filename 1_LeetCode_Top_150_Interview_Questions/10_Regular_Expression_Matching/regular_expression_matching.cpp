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

#include <string>
#include <vector>
using namespace std;

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
