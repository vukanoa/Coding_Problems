/*
    ============
    === HARD ===
    ============

    ===========================
    72) Edit Distance
    ===========================

    ============
    Description:
    ============

    Given two strings "word1" and "word2", return the minimum number of
    operations required to convert word1 to word2.

    You have the following three operations permitted on a word:
        - Insert a character
        - Delete a character
        - Insert a character

    =======================================================
    FUNCTION: int mindDistance(string word1, string word2);
    =======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  word1 = "horse", word2 = "ros"
    Output: 3

    --- Example 2 ---
    Input:  word1 = "intention", word2 = "execution"
    Output: 5

    *** Constraints ***
    0 <= word1.length, word2.length <= 500
    word1 and word2 consist of lowercase English letters

*/

#include <climits>
#include <cstring>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 11.21% */
/* Space Beats: 87.51% */

/* Time  Complexity: O(N * M) */
/* Space Complexity: O(N * M) */
class Solution_Top_Down__Memoization {
private:
    int memo[501][501];

public:
    int minDistance(string word1, string word2)
    {
        const int N = word1.size();
        const int M = word2.size();

        /* Memset */
        memset(memo, 0xff, sizeof(memo));

        /* Solve */
        return solve(0, 0, word1, word2);
    }

private:
    int solve(int i, int j, string& word1, string& word2)
    {
        const int N = word1.size();
        const int M = word2.size();

        if (i == N)
            return M - j;

        if (j == M)
            return N - i;

        if (memo[i][j] != -1)
            return memo[i][j];

        int replace_chr = INT_MAX;
        if (word1[i] != word2[j])
            replace_chr = 1 + solve(i+1, j+1, word1, word2);
        else
            replace_chr = 0 + solve(i+1, j+1, word1, word2);

        int delete_chr  = 1 + solve(i+1, j  , word1, word2);
        int insert_chr  = 1 + solve(i  , j+1, word1, word2);

        return memo[i][j] = min( {replace_chr, delete_chr, insert_chr} );
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 70.83% */
/* Space Beats: 73.29% */

/* Time  Complexity: O(N * M) */
/* Space Complexity: O(N * M) */
class Solution_Bottom_Up__Tabulation {
public:
    int minDistance(string word1, string word2)
    {
        const int N = word1.size();
        const int M = word2.size();

        vector<vector<int>> dp(N+1, vector<int>(M+1, INT_MAX));
        dp[N][M] = 0;

        /* Initialize last ROW */
        for (int j = M-1; j >= 0; j--)
            dp[N][j] = 1 + dp[N][j+1];

        /* Initialize last COL */
        for (int i = N-1; i >= 0; i--)
            dp[i][M] = 1 + dp[i+1][M];

        /* Solve */
        for (int i = N-1; i >= 0; i--)
        {
            for (int j = M-1; j >= 0; j--)
            {
                if (word1[i] != word2[j])
                    dp[i][j] = 1 + dp[i+1][j+1]; // Replace in word1 
                else
                    dp[i][j] = 0 + dp[i+1][j+1]; // Same letters

                dp[i][j] = min(dp[i][j], 1 + dp[i+1][j  ]); // Delete from word1
                dp[i][j] = min(dp[i][j], 1 + dp[i  ][j+1]); // Insert in   word2
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

/* Time  Beats: 64.13% */
/* Space Beats: 85.24% */

/* Time  Complexity: O(N * M) */
/* Space Complexity: O(2 * M) */
class Solution_Bottom_Up__Tabulation__Space_Optimized {
public:
    int minDistance(string word1, string word2)
    {
        const int N = word1.size();
        const int M = word2.size();

        vector<int> dp_next(M+1, INT_MAX);
        dp_next[M] = 0;

        /* Initialize last ROW */
        for (int j = M-1; j >= 0; j--)
            dp_next[j] = 1 + dp_next[j+1];

        /* Solve */
        for (int i = N-1; i >= 0; i--)
        {
            vector<int> dp_curr(M+1, INT_MAX);
            dp_curr[M] = N - i;

            for (int j = M-1; j >= 0; j--)
            {
                if (word1[i] != word2[j])
                    dp_curr[j] = 1 + dp_next[j+1]; // Replace in word1 
                else
                    dp_curr[j] = 0 + dp_next[j+1]; // Same letters

                dp_curr[j] = min(dp_curr[j], 1 + dp_next[j  ]); // Delete from word1
                dp_curr[j] = min(dp_curr[j], 1 + dp_curr[j+1]); // Insert in   word2
            }

            dp_next = std::move(dp_curr);
        }

        return dp_next[0];
    }
};
