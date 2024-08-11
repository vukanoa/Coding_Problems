#include <iostream>
#include <vector>

/*
    ============
    === HARD ===
    ============

    =================================================
    1568) Minimum Number of Days to Disconnect Island
    =================================================

    ============
    Description:
    ============

    You are given an m x n binary grid grid where 1 represents land and 0
    represents water. An island is a maximal 4-directionally (horizontal or
    vertical) connected group of 1's.

    The grid is said to be connected if we have exactly one island, otherwise
    is said disconnected.

    In one day, we are allowed to change any single land cell (1) into a water
    cell (0).

    Return the minimum number of days to disconnect the grid.

    =================================================
    FUNCTION: int minDays(vector<vector<int>>& grid);
    =================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: grid = [[0,1,1,0],[0,1,1,0],[0,0,0,0]]

    Output: 2
    Explanation: We need at least 2 days to get a disconnected grid.
    Change land grid[1][1] and grid[0][2] to water and get 2 disconnected
    island.


    --- Example 2 ---
    Input: grid = [[1,1]]
    Output: 2
    Explanation: Grid of full water is also disconnected ([[1,1]] -> [[0,0]]),
                 0 islands.


    *** Constraints ***
    m == grid.length
    n == grid[i].length
    1 <= m, n <= 30
    grid[i][j] is either 0 or 1.

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 79.88% */
/* Space Beats: 99.71% */

/* Time  Complexity: O( (ROWS * COLS)^2 ) */
/* Space Complexity: O(ROWS * COLS) */
class Solution {
public:
    int minDays(vector<vector<int>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        int min_days = 2; // 2 is the worst case scenario
        int islands  = count_islands(grid);

        if (islands != 1)
            return 0;

        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLS; j++)
            {
                if (grid[i][j] == 1)
                {
                    grid[i][j] = 0;

                    islands = count_islands(grid);

                    if (islands != 1)
                        return 1;

                    grid[i][j] = 1;
                }
            }
        }

        return 2;
    }

private:
    int count_islands(vector<vector<int>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        int islands = 0;

        // Count Islands
        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLS; j++)
            {
                if (grid[i][j] == 1)
                {
                    dfs(grid, i, j);
                    islands++;
                }
            }
        }

        // Restore original designation for islands
        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLS; j++)
            {
                if (grid[i][j] == 2)
                    grid[i][j] = 1;
            }
        }

        return islands;
    }


    void dfs(vector<vector<int>>& grid, int i, int j)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        if (i < 0 || j < 0 || i == ROWS || j == COLS || grid[i][j] != 1)
            return;

        grid[i][j] = 2;

        /* Signing Cross */
        dfs(grid, i-1, j  );
        dfs(grid, i+1, j  );
        dfs(grid, i  , j-1);
        dfs(grid, i  , j+1);
    }
};
