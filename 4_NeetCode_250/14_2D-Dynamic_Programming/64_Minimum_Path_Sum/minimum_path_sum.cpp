/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    63) Minimum Path Sum
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
#include <vector>
using namespace std;

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
class Solution_64_Tabulation {
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
