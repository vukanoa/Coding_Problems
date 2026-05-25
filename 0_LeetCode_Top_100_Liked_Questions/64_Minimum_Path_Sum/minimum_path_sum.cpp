/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    64) Minimum Path Sum
    ===========================

    ============
    Description:
    ============

    Given a "m x n" grid filled with non-negative numbers, find a path from top
    left to bottom right, which minimizes the sum of all numbers along its path

    =====
    Node: You can only move either down or right at any point in time.
    =====

    ====================================================
    FUNCTION: int minPathSum(vector<vector<int>>& grid);
    ====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  grid = [[1, 3, 1], [1, 5, 1], [4, 2, 1]]
    Output: 7

    --- Example 2 ---
    Input:  grid = [[1, 2, 3], [4, 5, 6]]
    Output: 12

    *** Constraints ***
    m == grid.length
    n == grid[i].length
    1 <= m, n <= 200
    0 <= grid[i][j] <= 100

*/

#include <climits>
#include <cstring>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 33.66% */
/* Space Beats: 80.55% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(ROWS * COLS) */
class Solution_Top_Down__Memoization {
private:
    int memo[201][201];

public:
    int minPathSum(vector<vector<int>>& grid)
    {
        /* Memset */
        memset(memo, 0xff, sizeof(memo));

        return solve(0, 0, grid);
    }

private:
    int solve(int row, int col, vector<vector<int>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        if (row >= ROWS || col >= COLS)
            return INT_MAX;

        if (row == ROWS-1 && col == COLS-1)
            return grid[row][col];

        if (memo[row][col] != -1)
            return memo[row][col];

        int move_down  = solve(row+1, col,   grid);
        int move_right = solve(row,   col+1, grid);

        return memo[row][col] = grid[row][col] + min(move_down, move_right);
    }

};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 38.74% */
/* Space Beats: 38.32% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(ROWS * COLS) */
class Solution_Bottom_Up__Tabulation {
public:
    int minPathSum(vector<vector<int>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        vector<vector<int>> dp(ROWS, vector<int>(COLS, INT_MAX));
        dp[0][0] = grid[0][0];

        /* Initialize 0th ROW */
        for (int col = 1; col < COLS; col++)
            dp[0][col] = dp[0][col-1] + grid[0][col];

        /* Initialize 0th COL */
        for (int row = 1; row < ROWS; row++)
            dp[row][0] = dp[row-1][0] + grid[row][0];

        /* Solve */
        for (int row = 1; row < ROWS; row++)
        {
            for (int col = 1; col < COLS; col++)
            {
                dp[row][col] = min(dp[row-1][col  ],
                                   dp[row  ][col-1]);

                dp[row][col] += grid[row][col];
            }
        }

        return dp[ROWS-1][COLS-1];
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same as above, though we only ever neet the very next row while doing DP.
    Thus, we can reduce Space Complexity from O(N) down to O(1).

*/

/* Time  Beats: 100.00% */
/* Space Beats:  80.21% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(COLS)        */
class Solution_Bottom_Up__Tabulation__Space_Optimized {
public:
    int minPathSum(vector<vector<int>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        vector<int> dp(COLS, INT_MAX);
        dp[0] = grid[0][0];

        /* Initialize 0th ROW */
        for (int col = 1; col < COLS; col++)
            dp[col] = dp[col-1] + grid[0][col];

        /* Solve */
        for (int row = 1; row < ROWS; row++)
        {
            dp[0] += grid[row][0];

            for (int col = 1; col < COLS; col++)
            {
                dp[col] = min(dp[col  ],
                              dp[col-1]);

                dp[col] += grid[row][col];
            }
        }

        return dp[COLS-1];
    }
};
