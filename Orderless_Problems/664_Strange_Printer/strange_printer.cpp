#include <iostream>

/*
    ============
    === HARD ===
    ============

    ===========================
    664) Strange Printer
    ===========================

    ============
    Description:
    ============

    There is a strange printer with the following two special properties:

        The printer can only print a sequence of the same character each time.
        At each turn, the printer can print new characters starting from and
        ending at any place and will cover the original existing characters.

    Given a string s, return the minimum number of turns the printer needed to
    print it.

    =======================================
    FUNCTION: int strangePrinter(string s);
    =======================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "aaabbb"
    Output: 2
    Explanation: Print "aaa" first and then print "bbb".

    --- Example 2 ---
    Input: s = "aba"
    Output: 2
    Explanation: Print "aaa" first and then print "b" from the second place of
    the string, which will cover the existing character 'a'.

    *** Constraints ***
    1 <= s.length <= 100
    s consists of lowercase English letters.

*/

/* Time  Beats: 65.41% */
/* Space Beats: 75.13% */

/* Time  Complexity: O(n^3) */
/* Space Complexity: O(n^2) */
class Solution {
public:
    int strangePrinter(std::string s) {
        const int n = s.length();

        std::vector<std::vector<int>> dp(n, std::vector<int>(n, INT_MAX));

        for(int i = 0; i < n; i++)
            dp[i][i] = 1;

        for (int l = 2; l < n+1; l++)
        {
            for(int i = 0; i < n-l+1; i++)
            {
                int j = i+l-1;

                dp[i][j] = dp[i+1][j] + 1;

                for(int k = i+1; k < j+1; k++)
                {
                    if(s[i] == s[k])
                        dp[i][j] = min(dp[i][j], dp[i][k-1] + ((j>k) ? dp[k+1][j] : 0));
                }
            }
        }

        return dp[0][n-1];
    }
};
