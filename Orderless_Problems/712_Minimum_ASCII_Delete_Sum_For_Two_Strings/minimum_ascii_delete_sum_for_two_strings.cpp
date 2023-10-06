#include <iostream>

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

/*
    ------------
    --- IDEA ---
    ------------

    It's the same technique, but a bit different for the base cases, as in
    "Longest Common Subsequence".

*/

/* Time  Beats: 83.22% */
/* Space Beats: 22.98% */

/* Time  Complexity: O(M * N) */
/* Space Complexity: O(M * N) */
class Solution {
public:
    int minimumDeleteSum(std::string s1, std::string s2)
    {
        int M = s2.length();
        int N = s1.length();

        std::vector<std::vector<int>> dp(M+1, std::vector<int>(N+1, 0));

        // As if: s1=""    s2="eat"
        for (int i = M-1; i >= 0; i--)
            dp[i][N] = s2[i] + dp[i+1][N];

        // As if: s1="sea" s2=""
        for (int j = N-1; j >= 0; j--)
            dp[M][j] = s1[j] + dp[M][j+1];

        for (int i = M-1; i >= 0; i--)
        {
            for (int j = N-1; j >= 0; j--)
            {
                if (s1[j] == s2[i])
                    dp[i][j] = dp[i+1][j+1]; // Diagonal
                else
                {
                    int right = dp[i  ][j+1];
                    int down  = dp[i+1][j  ];

                    if ((s1[j] + right) < (s2[i] + down))
                        dp[i][j] = s1[j] + right;
                    else
                        dp[i][j] = s2[i] + down;
                }
            }
        }

        return dp[0][0];
    }
};
