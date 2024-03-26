#include <iostream>

/*
    ==============
    === MEDIUM ===
    ==============

    =======================
    695) Max Area of Island
    =======================

    ============
    Description:
    ============

    You are given an m x n binary matrix grid. An island is a group of 1's
    (representing land) connected 4-directionally (horizontal or vertical.)
    You may assume all four edges of the grid are surrounded by water.

    The area of an island is the number of cells with a value 1 in the island.

    Return the maximum area of an island in grid. If there is no island, return
    0.

    ========================================================
    FUNCTION: int maxAreaOfIsland(vector<vector<int>& grid);
    ========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: grid = [[0,0,1,0,0,0,0,1,0,0,0,0,0],
                   [0,0,0,0,0,0,0,1,1,1,0,0,0],
                   [0,1,1,0,1,0,0,0,0,0,0,0,0],
                   [0,1,0,0,1,1,0,0,1,0,1,0,0],
                   [0,1,0,0,1,1,0,0,1,1,1,0,0],
                   [0,0,0,0,0,0,0,0,0,0,1,0,0],
                   [0,0,0,0,0,0,0,1,1,1,0,0,0],
                   [0,0,0,0,0,0,0,1,1,0,0,0,0]]
    Output: 6
    Explanation: The answer is not 11, because the island must be connected
                 4-directionally.



    --- Example 2 ---
    Input: grid = [[0,0,0,0,0,0,0,0]]
    Output: 0


    *** Constraints ***
    m == grid.length
    n == grid[i].length
    1 <= m, n <= 50
    grid[i][j] is either 0 or 1.

*/

/*
    ------------
    --- IDEA ---
    ------------

    It's almost equivalent to the problem number 200. "Number of Islands".
    Definitely check that problem.

*/

/* Time  Beats: 99.71% */
/* Space Beats: 70.23% */

/* Time  Complexity: O(m * n) */
/* Space Complexity: O(m * n) */
class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        int max_area = 0;

        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLS; j++)
            {
                if (grid[i][j] == 1)
                {
                    int area = 0;
                    dfs(grid, i, j, area);

                    max_area = std::max(max_area, area);
                }
            }
        }

        return max_area;
    }

private:
    void dfs(std::vector<std::vector<int>>& grid, int i, int j, int& area)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        if (i < 0 || j < 0 || i == ROWS || j == COLS || grid[i][j] != 1)
            return;

        area++;
        grid[i][j] = 2; // Don't traverse it twice. Mark as traversed.

        dfs(grid, i-1, j  , area);
        dfs(grid, i+1, j  , area);
        dfs(grid, i  , j-1, area);
        dfs(grid, i  , j+1, area);
    }
};
