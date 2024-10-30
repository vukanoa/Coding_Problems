#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    =======================================
    2684) Maximum Number of Moves in a Grid
    =======================================

    ============
    Description:
    ============

    You are given a 0-indexed m x n matrix grid consisting of positive
    integers.

    You can start at any cell in the first column of the matrix, and traverse
    the grid in the following way:

        From a cell (row, col), you can move to any of the cells:

            (row - 1, col + 1), (row, col + 1) and (row + 1, col + 1)

        such that the value of the cell you move to, should be strictly bigger
        than the value of the current cell.

    Return the maximum number of moves that you can perform.

    ==================================================
    FUNCTION: int maxMoves(vector<vector<int>>& grid);
    ==================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: grid = [[2,4,3,5],[5,4,9,3],[3,4,2,11],[10,9,13,15]]
    Output: 3
    Explanation: We can start at the cell (0, 0) and make the following moves:
    - (0, 0) -> (0, 1).
    - (0, 1) -> (1, 2).
    - (1, 2) -> (2, 3).
    It can be shown that it is the maximum number of moves that can be made.

    --- Example 2 ---
    Input: grid = [[3,2,4],[2,1,9],[1,1,7]]
    Output: 0
    Explanation: Starting from any cell in the first column we cannot perform
                 any moves.


    *** Constraints ***
    m == grid.length
    n == grid[i].length
    2 <= m, n <= 1000
    4 <= m * n <= 10^5
    1 <= grid[i][j] <= 10^6

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 32.61% */
/* Space Beats: 57.28% */

/* Time  Complexity: O(m * n) */
/* Space Complexity: O(m * n) */
class Solution {
public:
    int maxMoves(vector<vector<int>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();
        vector<vector<int>> dp(ROWS, vector<int>(COLS, 0));

        // Initialize the last column to 1, in every ROW
        for (int i = 0; i < ROWS; i++)
            dp[i][COLS - 1] = 1;

        // Process from the second-to-last column to the 0th, in every row
        for (int j = COLS - 2; j >= 0; j--)
        {
            for (int i = 0; i < ROWS; i++)
            {
                int curr = grid[i][j];

                // Check the cell East
                int max_move = (curr < grid[i][j + 1]) * dp[i][j + 1];

                // Check the cell North-East
                if (i > 0 && curr < grid[i - 1][j + 1])
                    max_move = max(max_move, dp[i - 1][j + 1]);

                // Check the cell South-East
                if (i < ROWS - 1 && curr < grid[i + 1][j + 1])
                    max_move = max(max_move, dp[i + 1][j + 1]);

                dp[i][j] = 1 + max_move;
            }
        }

        // Calculate the maximum moves
        int result = 0;
        for (int i = 0; i < ROWS; i++)
            result = max(result, dp[i][0]);

        return result - 1; // subtracting 1 as per initial setup
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 93.48% */
/* Space Beats: 25.57% */

/* Time  Complexity: O(n * m) */
/* Space Complexity: O(n * m) */
class Solution_Memoization {
public:
    int dfs(vector<vector<int>>& grid, vector<vector<int>>& dp, int prev, int i, int j)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        if (i < 0 || j < 0 || i >= ROWS || j >= COLS)
            return 0;

        int curr = grid[i][j];

        if (curr <= prev)
            return 0;

        if (dp[i][j] != -1)
            return dp[i][j];

        int max_move = 1 + dfs(grid, dp, curr, i-1, j+1);

        for (int i0 = i; i0 <= i+1; i0++)
        {
            if (max_move == COLS - j)
                break; // early stop pruning

            max_move = max(max_move, 1 + dfs(grid, dp, curr, i0, j+1));
        }

        return dp[i][j] = max_move;
    }

    int maxMoves(vector<vector<int>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        vector<vector<int>> dp(ROWS, vector<int>(COLS, -1));

        int result = 0;
        for (int i = 0; i < ROWS; i++)
        {
            if (result == COLS)
                break; // early stop

            result = max(result, dfs(grid, dp, -1, i, 0));
        }

        return result-1;
    }
};
