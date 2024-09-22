#include <iostream>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    576) Out of Boundary Paths
    ===========================

    ============
    Description:
    ============

    There is an m x n grid with a ball. The ball is initially at the position
    [startRow, startColumn]. You are allowed to move the ball to one of the
    four adjacent cells in the grid (possibly out of the grid crossing the grid
    boundary). You can apply at most maxMove moves to the ball.

    Given the five integers m, n, maxMove, startRow, startColumn, return the
    number of paths to move the ball out of the grid boundary. Since the answer
    can be very large, return it modulo 109 + 7.

    ==================================================================================
    FUNCTION: int findPaths(int m, int n, int maxMove, int startRow, int startColumn);
    ==================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: m = 2, n = 2, maxMove = 2, startRow = 0, startColumn = 0
    Output: 6

    --- Example 2 ---
    Input: m = 1, n = 3, maxMove = 3, startRow = 0, startColumn = 1
    Output: 12


    *** Constraints ***
    1 <= m, n <= 50
    0 <= maxMove <= 50
    0 <= startRow < m
    0 <= startColumn < n

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 91.80% */
/* Space Beats: 78.50% */

/* Time  Complexity: O(N * M * Moves) */
/* Space Complexity: O(N * M * Moves) */
class Solution {
public:

    int dp[51][51][51];

    long long mod = 1e9+7;

    int findPaths(int n, int m, int maxMove, int startRow, int startColumn)
    {
        memset(dp , -1 , sizeof(dp));

        return dfs(startRow, startColumn, n, m, maxMove);
    }

private:
    int dfs(int i, int j, int n, int m, int moves)
    {
        if (i < 0 || i >= n || j < 0 || j >= m)
            return 1;

        if (moves <= 0)
            return 0;

        if (dp[i][j][moves] != -1)
            return dp[i][j][moves];

        int up    = dfs(i-1 , j , n , m , moves-1);
        int down  = dfs(i+1 , j , n , m , moves-1);
        int left  = dfs(i , j-1 , n , m , moves-1);
        int right = dfs(i , j+1 , n , m , moves-1);

        return dp[i][j][moves] = (up % mod + down % mod + left % mod + right % mod) % mod;
    }
};
