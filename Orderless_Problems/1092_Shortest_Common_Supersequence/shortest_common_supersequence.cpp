/*
    ============
    === HARD ===
    ============

    ===================================
    1092) Shortest Common Supersequence
    ===================================

    ============
    Description:
    ============


    Given two strings str1 and str2, return the shortest string that has both
    str1 and str2 as subsequences. If there are multiple valid strings, return
    any of them.

    A string s is a subsequence of string t if deleting some number of
    characters from t (possibly 0) results in the string s.

    =======================================================================
    FUNCTION: string shortestCommonSupersequence(string str1, string str2);
    =======================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: str1 = "abac", str2 = "cab"
    Output: "cabac"
    Explanation:
    str1 = "abac" is a subsequence of "cabac" because we can delete the first "c".
    str2 = "cab" is a subsequence of "cabac" because we can delete the last "ac".
    The answer provided is the shortest such string that satisfies these properties.

    --- Example 2 ---
    Input: str1 = "aaaaaaaa", str2 = "aaaaaaaa"
    Output: "aaaaaaaa"


    *** Constraints ***
    1 <= str1.length, str2.length <= 1000
    str1 and str2 consist of lowercase English letters.

*/

#include <algorithm>
#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    If you've never solved "LCS"(Longest Commong Subsequence), then go and do
    that one first. If you don't understand that, you won't have a chance
    solving this one.

    Once you've learned that one, read through the code and I'm sure you're
    going to get it.

*/

/* Time  Beats: 38.39% */
/* Space Beats: 70.92% */

/* Time  Complexity: O(N * M) */
/* Space Complexity: O(N * M) */
class Solution_LCS_DP {
public:
    string shortestCommonSupersequence(string str1, string str2)
    {
        const int SIZE_1 = str1.length();
        const int SIZE_2 = str2.length();

        vector<vector<int>> dp(SIZE_1 + 1, vector<int>(SIZE_2 + 1, 0));

        // When str2 is empty, the supersequence is str1 itself
        for (int row = 0; row <= SIZE_1; row++)
            dp[row][0] = row;

        // When str1 is empty, the supersequence is str2 itself
        for (int col = 0; col <= SIZE_2; col++)
            dp[0][col] = col;

        for (int row = 1; row <= SIZE_1; row++)
        {
            for (int col = 1; col <= SIZE_2; col++)
            {
                if (str1[row - 1] == str2[col - 1]) // Match
                {
                    // Inherit the length from the diagonal + 1
                    dp[row][col] = dp[row - 1][col - 1] + 1;
                }
                else
                {
                    // Take the minimum length option + 1
                    dp[row][col] = min(dp[row - 1][col], dp[row][col - 1]) + 1;
                }
            }
        }

        string supersequence = "";
        int row = SIZE_1;
        int col = SIZE_2;

        while (row > 0 && col > 0)
        {
            if (str1[row - 1] == str2[col - 1]) // Match
            {
                // Take it from diagonal
                supersequence += str1[row - 1];
                row--;
                col--;
            }
            else if (dp[row - 1][col] < dp[row][col - 1])
            {
                // If str1’s character is part of the supersequence, move up
                supersequence += str1[row - 1];
                row--;
            }
            else
            {
                // If str2’s character is part of the supersequence, move left
                supersequence += str2[col - 1];
                col--;
            }
        }

        // Append any remaining characters
        // If there are leftover characters in str1
        while (row > 0)
        {
            supersequence += str1[row - 1];
            row--;
        }

        // If there are leftover characters in str2
        while (col > 0)
        {
            supersequence += str2[col - 1];
            col--;
        }

        // Reverse the built sequence to get the correct order
        reverse(supersequence.begin(), supersequence.end());

        return supersequence;
    }
};
