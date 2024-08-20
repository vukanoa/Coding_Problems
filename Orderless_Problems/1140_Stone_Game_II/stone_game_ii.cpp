#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    1140) Stone Game II
    ===========================

    ============
    Description:
    ============

    Alice and Bob continue their games with piles of stones.  There are a
    number of piles arranged in a row, and each pile has a positive integer
    number of stones piles[i].  The objective of the game is to end with the
    most stones.

    Alice and Bob take turns, with Alice starting first.  Initially, M = 1.

    On each player's turn, that player can take all the stones in the first X
    remaining piles, where 1 <= X <= 2M.  Then, we set M = max(M, X).

    The game continues until all the stones have been taken.

    Assuming Alice and Bob play optimally, return the maximum number of stones
    Alice can get.

    ==============================================
    FUNCTION: int stoneGameII(vector<int>& piles);
    ==============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: piles = [2,7,9,4,4]
    Output: 10
    Explanation:  If Alice takes one pile at the beginning, Bob takes two
                  piles, then Alice takes 2 piles again. Alice can get 2 + 4 +
                  4 = 10 piles in total. If Alice takes two piles at the
                  beginning, then Bob can take all three piles left. In this
                  case, Alice get 2 + 7 = 9 piles in total. So we return 10
                  since it's larger.


    --- Example 2 ---
    Input: piles = [1,2,3,4,5,100]
    Output: 104


    *** Constraints ***
    1 <= piles.length <= 100
    1 <= piles[i] <= 10^4

*/

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 54.50% */
/* Space Beats: 45.59% */

/* Time  Complexity: O(n^3) */
/* Space Complexity: O(n^2) */
class Solution {
public:
    int stoneGameII(vector<int>& piles)
    {
        if (piles.size() == 1)
            return piles[0];

        const int n = piles.size();
        vector<vector<vector<int>>> dp(2, vector<vector<int>>(n, vector<int>(n, -1)));

        return dfs(piles, 1, 0, 1, dp);
    }

private:
    int dfs(vector<int>& piles, int alice, int i, int M, vector<vector<vector<int>>>& dp)
    {
        if (i >= piles.size())
            return 0;

        if (dp[alice][i][M] != -1)
            return dp[alice][i][M];

        int result = (alice == 1) ? 0 : INT_MAX;

        int total = 0;
        for (int X = 1; X <= 2 * M; X++)
        {
            if (i + X - 1 >= piles.size())
                break;

            total += piles[i + X - 1];

            if (alice == 1) // Alice tries to maximize her score
                result = max(result, total + dfs(piles, alice ^ 1, i + X, max(M, X), dp));
            else // Bob tries to minimize Alice's score
                result = min(result, dfs(piles, alice ^ 1, i + X, max(M, X), dp));
        }

        dp[alice][i][M] = result;

        return result;
    }
};
