#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ==============================
    1254) Number of Closed Islands
    ==============================

    ============
    Description:
    ============

    Given a 2D grid consists of 0s (land) and 1s (water).  An island is a
    maximal 4-directionally connected group of 0s and a closed island is an
    island totally (all left, top, right, bottom) surrounded by 1s.

    Return the number of closed islands.

    ======================================================
    FUNCTION: int closedIsland(vector<vector<int>>& grid);
    ======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: grid = [[1,1,1,1,1,1,1,0],
                   [1,0,0,0,0,1,1,0],
                   [1,0,1,0,1,1,1,0],
                   [1,0,0,0,0,1,0,1],
                   [1,1,1,1,1,1,1,0]]
    Output: 2
    Explanation:
    Islands in gray are closed because they are completely surrounded by water
    (group of 1s).



    --- Example 2 ---
    Input: grid = [[0,0,1,0,0],
                   [0,1,0,1,0],
                   [0,1,1,1,0]]
    Output: 1



    --- Example 3 ---
    Input: grid = [[1,1,1,1,1,1,1],
                   [1,0,0,0,0,0,1],
                   [1,0,1,1,1,0,1],
                   [1,0,1,0,1,0,1],
                   [1,0,1,1,1,0,1],
                   [1,0,0,0,0,0,1],
                   [1,1,1,1,1,1,1]]
    Output: 2



    *** Constraints ***
    1 <= grid.length, grid[0].length <= 100
    0 <= grid[i][j] <=1

*/

/*
    ------------
    --- IDEA ---
    ------------

    The Crux of problems like this one is to "read it in reverse". Instead of
    aiming at finding all the "Closed Islands", aim to find all the "Open
    Islands".

    Anytime you find an "Open Island", mark it(by changing it from 0 to 2 or
    something similar).

    So what is, in this problem, a "Open Island"?
    An "Open Island" is a land that is connected to the edge.

    Therefore, traverse: (Clockwise)
        1. First row      // Upper  edge
        2. Last  column   // Right  edge
        3. Last  row      // Bottom edge
        4. First column   // Left   edge

    Mark every land that is connected to one or more edges.

    After that, start at position (1, 1) and traverse until (ROWS-1, COLS-1).
    Count how any unconnected Islands are there. That is what we are asked for.

    That is how you get the number of "Closed Islands".

*/

/* Time  Beats: 94.40% */
/* Space Beats: 95.99% */

/* Time  Complexity: O(M * N) */
/* Space Complexity: O(M * N) */
class Solution {
public:
    int closedIsland(std::vector<std::vector<int>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        int result = 0;

        // First Row
        for (int j = 0; j < COLS; j++)
            dfs_from_edges(grid, 0, j);

        // Last Col
        for (int i = 0; i < ROWS; i++)
            dfs_from_edges(grid, i, COLS-1);

        // Last Row
        for (int j = COLS-1; j >= 0; j--)
            dfs_from_edges(grid, ROWS-1, j);

        // First Col
        for (int i = ROWS-1; i >= 0; i--)
            dfs_from_edges(grid, i, 0);

        /* Count Closed Islands */
        for (int i = 1; i < ROWS-1; i++)
        {
            for (int j = 1; j < COLS-1; j++)
            {
                if (grid[i][j] == 0)
                {
                    dfs_inside(grid, i, j);
                    result++;
                }
            }
        }

        /* Restore grid matrix back to Original */
        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLS; j++)
            {
                if (grid[i][j] == 2 || grid[i][j] == 3)
                    grid[i][j] = 0;
            }
        }

        return result;
    }

private:
    void dfs_from_edges(std::vector<std::vector<int>>& grid, int i, int j)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        if (i < 0 || j < 0 || i == ROWS || j == COLS)
            return;

        if (grid[i][j] != 0)
            return;

        grid[i][j] = 2;

        /* Signing Cross */
        dfs_from_edges(grid, i-1, j  ); // Up
        dfs_from_edges(grid, i+1, j  ); // Down
        dfs_from_edges(grid, i  , j-1); // Left
        dfs_from_edges(grid, i  , j+1); // Right
    }

    void dfs_inside(std::vector<std::vector<int>>& grid, int i, int j)
    {
        if (grid[i][j] != 0)
            return;

        grid[i][j] = 3;

        /* Signing Cross */
        dfs_inside(grid, i-1, j  ); // Up
        dfs_inside(grid, i+1, j  ); // Down
        dfs_inside(grid, i  , j-1); // Left
        dfs_inside(grid, i  , j+1); // Right
    }
};
