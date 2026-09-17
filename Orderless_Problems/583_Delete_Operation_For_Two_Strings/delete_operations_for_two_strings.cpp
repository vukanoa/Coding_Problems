/*
    ==============
    === MEDIUM ===
    ==============

    ======================================
    583) Delete Operations for Two Strings
    ======================================

    ============
    Description:
    ============

    Given two strings word1 and word2, return the minimum number of steps
    required to make word1 and word2 the same.

    In one step, you can delete exactly one character in either string.

    ======================================================
    FUNCTION: int minDistance(string word1, string word2);
    ======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: word1 = "sea", word2 = "eat"
    Output: 2
    Explanation: You need one step to make "sea" to "ea" and another step to
                 make "eat" to "ea".

    --- Example 2 ---
    Input: word1 = "leetcode", word2 = "etco"
    Output: 4


    *** Constraints ***
    1 <= word1.length, word2.length <= 500
    word1 and word2 consist of only lowercase English letters.

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

/* Time  Beats: 97.94% */
/* Space Beats: 90.19% */

/* Time  Complexity: O(N * M) */
/* Space Complexity: O(M)     */
class Solution_Bottom_Up__Tabulation__Space_Optimized {
public:
    int minDistance(string word1, string word2)
    {
        const int N = word1.size();
        const int M = word2.size();

        if (M > N)
            return minDistance(word2, word1);

        vector<int> dp(M+1, 0);

        for (int i = 1; i <= N; i++)
        {
            int prev = 0;

            for (int j = 1; j <= M; j++)
            {
                int tmp = dp[j];

                if (word1[i-1] == word2[j-1])
                    dp[j] = 1 + prev;          // Diagonal
                else
                    dp[j] = max(dp[j],         // Up
                                dp[j-1]);      // Left

                prev = tmp;
            }
        }

        return N + M - 2*dp[M];
    }
};
