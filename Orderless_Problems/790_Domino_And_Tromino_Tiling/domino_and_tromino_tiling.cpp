/*
    ==============
    === MEDIUM ===
    ==============

    ==============================
    790) Domino and Tromino Tiling
    ==============================

    ============
    Description:
    ============

    You have two types of tiles: a 2 x 1 domino shape and a tromino shape. You
    may rotate these shapes.

    Given an integer n, return the number of ways to tile an 2 x n board. Since
    the answer may be very large, return it modulo 109 + 7.

    In a tiling, every square must be covered by a tile. Two tilings are
    different if and only if there are two 4-directionally adjacent cells on
    the board such that exactly one of the tilings has both squares occupied by
    a tile.

    ================================
    FUNCTION: int numTilings(int n);
    ================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 3
    Output: 5
    Explanation: The five different ways are show above.

    --- Example 2 ---
    Input: n = 1
    Output: 1


    *** Constraints ***
    1 <= n <= 1000

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Classic "Coin Change" type of Dynamic Programming.

    The only difference is that we do NOT start from i = 1 because the pattern
    just doesn't work. Instead we must begin at i=4 and the pattern is the same
    for all the other values of n.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  33.74% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
     int numTilings(int N)
     {
        const int MOD = 1e9 + 7;

        vector<long long> dp(1001, 0); // O(n) Space Complexity
        dp[1] = 1;
        dp[2] = 2;
        dp[3] = 5;

        if (N <= 3)
            return dp[N];

        for (int i = 4; i <= N; i++)
        {
            dp[i] = 2*dp[i-1] + dp[i-3];
            dp[i] %= MOD;
        }

        return dp[N];
    }
};
