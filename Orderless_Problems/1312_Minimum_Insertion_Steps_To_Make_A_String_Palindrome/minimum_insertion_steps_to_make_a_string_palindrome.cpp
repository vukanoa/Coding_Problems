#include <iostream>
#include <vector>

/*
    ============
    === HARD ===
    ============

    =========================================================
    1312) Minimum Insertion Steps to Make a String Palindrome
    =========================================================

    ============
    Description:
    ============

    Given a string s. In one step you can insert any character at any index of
    the string.

    Return the minimum number of steps to make s palindrome.

    A Palindrome String is one that reads the same backward as well as forward.

    ======================================
    FUNCTION: int minInsertions(string s);
    ======================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "zzazz"
    Output: 0
    Explanation: The string "zzazz" is already palindrome we do not need any
                 insertions.

    --- Example 2 ---
    Input: s = "mbadm"
    Output: 2
    Explanation: String can be "mbdadbm" or "mdbabdm".

    --- Example 3 ---
    Input: s = "leetcode"
    Output: 5
    Explanation: Inserting 5 characters the string becomes "leetcodocteel".


    *** Constraints ***
    1 <= s.length <= 500
    s consists of lowercase English letters.

*/

using namespace std;


/*
    ------------
    --- IDEA ---
    ------------

    TODO
    (Classic Memoization)

*/

/* Time  Beats: 7.40% */
/* Space Beats: 9.03% */

/* Time  Complexity: O(n^2) */
/* Space Complexity: O(n)   */
class Solution_Memoization {
class Solution {
public:
    int minInsertions(string s)
    {
        const int n = s.length();

        string s_reverse = s;
        reverse(s_reverse.begin(), s_reverse.end());

        vector<vector<int>> memo(n + 1, vector<int>(n + 1, -1));

        return n - LCS(s, s_reverse, n, n, memo);
    }

private:
    int LCS(string& s1, string& s2, int m, int n, vector<vector<int>>& memo)
    {
        if (m == 0 || n == 0)
            return 0;

        if (memo[m][n] != -1)
            return memo[m][n];

        if (s1[m-1] == s2[n-1])
            return memo[m][n] = 1 + LCS(s1, s2, m-1, n-1, memo);

        return memo[m][n] = max(LCS(s1, s2, m-1, n  , memo),
                                LCS(s1, s2, m  , n-1, memo));
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Iterative Dynamic Programming approach.

*/

/* Time  Beats: 25.70% */
/* Space Beats:  9.03% */

/* Time  Complexity: O(n^2) */
/* Space Complexity: O(n)   */
class Solution_DP_Iterative {
class Solution {
public:
    int minInsertions(string s)
    {
        const int n = s.length();

        string s_reverse = s;
        reverse(s_reverse.begin(), s_reverse.end());

        return n - LCS(s, s_reverse, n, n);
    }

private:
    int LCS(string& s1, string& s2, int M, int n)
    {
        vector<vector<int>> dp(n+1, vector<int>(n+1));

        for (int row = 0; row <= M; row++)
        {
            for (int col = 0; col <= n; col++)
            {
                if (row == 0 || col == 0)
                {
                    dp[row][col] = 0; // One of the two strings is empty
                }
                else if (s1[row-1] == s2[col-1])
                {
                    dp[row][col] = 1 + dp[row-1][col-1];
                }
                else
                {
                    dp[row][col] = max(dp[row-1][col  ],
                                       dp[row  ][col-1]);
                }
            }
        }

        return dp[M][n];
    }
};
