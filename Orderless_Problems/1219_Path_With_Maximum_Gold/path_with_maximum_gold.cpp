#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ============================
    1219) Path with Maximum Gold
    ============================

    ============
    Description:
    ============

    In a gold mine grid of size m x n, each cell in this mine has an integer
    representing the amount of gold in that cell, 0 if it is empty.

    Return the maximum amount of gold you can collect under the conditions:

        + Every time you are located in a cell you will collect all the gold in
          that cell.

        + From your position, you can walk one step to the left, right, up, or
          down.

        + You can't visit the same cell more than once.

        + Never visit a cell with 0 gold.

        + You can start and stop collecting gold from any position in the grid
          that has some gold.

    ========================================================
    FUNCTION: int getMaximumGold(vector<vector<int>>& grid);
    ========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    +-----+-----+-----+
    |  0  |  6  |  0  |
    +-----+-----+-----+
    |  5  |  8  |  7  |
    +-----+-----+-----+
    |  0  |  9  |  0  |
    +-----+-----+-----+

    Input: grid = [[0,6,0],[5,8,7],[0,9,0]]
    Output: 24
    Explanation:
    [[0,6,0],
     [5,8,7],
     [0,9,0]]
    Path to get the maximum gold, 9 -> 8 -> 7.

    --- Example 2 ---
    Input: grid = [[1,0,7],[2,0,6],[3,4,5],[0,3,0],[9,0,20]]
    Output: 28
    Explanation:
    [[1,0,7],
     [2,0,6],
     [3,4,5],
     [0,3,0],
     [9,0,20]]
    Path to get the maximum gold, 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7.


    *** Constraints ***
    m == grid.length
    n == grid[i].length
    1 <= m, n <= 15
    0 <= grid[i][j] <= 100
    There are at most 25 cells containing gold.

*/

/*
    ------------
    --- IDEA ---
    ------------

    Standard DFS problem. If you are unfamiliar with this kind of problem, then
    make sure to check: LeetCode 200 - Number of Islands.

    It's a fairly simple problem and technique once you get the hang of it.

*/

/* Time  Beats: 37.24% */
/* Space Beats: 28.03% */

/* Time  Complexity: O(m * n * 4^(m*n)) */
/* Space Complexity: O(4^(m * n))       */
class Solution {
public:
    int getMaximumGold(std::vector<std::vector<int>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        int result = 0;

        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLS; j++)
            {
                if (grid[i][j] > 0)
                    result = std::max(result, dfs(grid, i, j));
            }
        }

        return result;
    }

private:
    int dfs(std::vector<std::vector<int>>& grid, int i, int j)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        if (i < 0 || j < 0 || i == ROWS || j == COLS || grid[i][j] == 0)
            return 0;

        int curr_cell_gold = grid[i][j];
        grid[i][j] = 0; // To prevent visiting the same cell more than once

        int up    = dfs(grid, i-1, j  );
        int down  = dfs(grid, i+1, j  );
        int left  = dfs(grid, i  , j-1);
        int right = dfs(grid, i  , j+1);

        grid[i][j] = curr_cell_gold; // Return original gold from that cell

        return curr_cell_gold + std::max( {up, down, left, right} );
    }
};
