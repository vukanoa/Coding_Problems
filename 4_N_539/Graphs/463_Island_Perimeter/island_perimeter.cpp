#include <iostream>
#include <vector>

/*
    ============
    === EASY ===
    ============

    ===========================
    463) Island Perimeter
    ===========================

    ============
    Description:
    ============

    You are given row x col grid representing a map where grid[i][j] = 1
    represents land and grid[i][j] = 0 represents water.

    Grid cells are connected horizontally/vertically (not diagonally). The grid
    is completely surrounded by water, and there is exactly one island (i.e.,
    one or more connected land cells).

    The island doesn't have "lakes", meaning the water inside isn't connected
    to the water around the island. One cell is a square with side length 1.
    The grid is rectangular, width and height don't exceed 100. Determine the
    perimeter of the island.

    =====================================================
    FUNCTION: islandPerimeter(vector<vector<int>>& grid);
    =====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    +-----+-----+-----+-----+
    |     |  X  |     |     |
    +-----+-----+-----+-----+
    |  X  |  X  |  X  |     |
    +-----+-----+-----+-----+
    |     |  X  |     |     |
    +-----+-----+-----+-----+
    |  X  |  X  |     |     |
    +-----+-----+-----+-----+

    Input: grid = [[0,1,0,0],[1,1,1,0],[0,1,0,0],[1,1,0,0]]
    Output: 16
    Explanation: The perimeter is the 16 yellow stripes in the image above.

    --- Example 2 ---
    Input: grid = [[1]]
    Output: 4

    --- Example 3 ---
    Input: grid = [[1,0]]
    Output: 4


    *** Constraints ***
    row == grid.length
    col == grid[i].length
    1 <= row, col <= 100
    grid[i][j] is 0 or 1.
    There is exactly one island in grid.

*/

/*
    ------------
    --- IDEA ---
    ------------

    Almost equivalent to problem "Number of Islands", so check out that one.

*/

/* Time  Beats: 79.80% */
/* Space Beats: 24.85% */

/* Time  Complexity: O(4^(M * N)) */
/* Space Complexity: O(M * N) */
class Solution {
public:
    int islandPerimeter(std::vector<std::vector<int>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        if (ROWS == 1 && COLS == 0)
            return 4;

        int perimeter = 0;

        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLS; j++)
            {
                if (grid[i][j] == 1)
                {
                    dfs(grid, i, j, perimeter);

                    // GOTO out of both loops
                    i = ROWS;
                    break;
                }
            }
        }

        return perimeter;
    }

private:
    void dfs(std::vector<std::vector<int>>& grid, int i, int j, int& perimeter)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        if (i < 0 || j < 0 || i == ROWS || j == COLS || grid[i][j] != 1)
            return;

        grid[i][j] = 2;

        if (i == 0      || grid[i-1][j  ] == 0)   // Up
            perimeter++;

        if (i == ROWS-1 || grid[i+1][j  ] == 0)   // Down
            perimeter++;

        if (j == 0      || grid[i  ][j-1] == 0)   // Left
            perimeter++;

        if (j == COLS-1 || grid[i  ][j+1] == 0)   // Right
            perimeter++;

        dfs(grid, i-1, j  , perimeter);
        dfs(grid, i+1, j  , perimeter);
        dfs(grid, i  , j-1, perimeter);
        dfs(grid, i  , j+1, perimeter);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same as above, just writen more concisely.

*/

/* Time  Beats: 83.70% */
/* Space Beats: 25.46% */

/* Time  Complexity: O(4^(M * N)) */
/* Space Complexity: O(M * N) */
class Solution {
public:
    int islandPerimeter(std::vector<std::vector<int>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        int perimeter = 0;

        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLS; j++)
            {
                if (grid[i][j] == 1)
                    return dfs(grid, i, j);
            }
        }

        return 0;
    }

private:
    int dfs(std::vector<std::vector<int>>& grid, int i, int j)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        if (i < 0 || j < 0 || i == ROWS || j == COLS || grid[i][j] == 0)
            return 1;

        if (grid[i][j] == 2)
            return 0;

        grid[i][j] = 2;

        int perimeter = 0;
        perimeter += dfs(grid, i-1, j  );
        perimeter += dfs(grid, i+1, j  );
        perimeter += dfs(grid, i  , j-1);
        perimeter += dfs(grid, i  , j+1);

        return perimeter;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This one is much more Space efficient for it does not use recursion.
    However I think this was not the point of this problem, but it is faster
    on LeetCode, so here it is.

    The point of this problem is to practice "Number of Islands" kind of
    problem.

*/

/* Time  Beats: 93.74% */
/* Space Beats: 79.44% */

/* Time  Complexity: O(M * N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int islandPerimeter(std::vector<std::vector<int>>& grid)
    {
        int perimeter = 0;
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        for(int i = 0; i < ROWS; i++)
        {
            for(int j = 0; j < COLS; j++)
            {
                if(grid[i][j] == 1)
                {
                    // Unconnected cell
                    perimeter += 4;

                    // Check if it's connected Upwards
                    if(i > 0        && grid[i-1][j] == 1)
                        perimeter -= 1;

                    // Check if it's connected Downwards
                    if(i < ROWS - 1 && grid[i+1][j] == 1)
                        perimeter -= 1;

                    // Check if it's connected to the Left
                    if(j > 0        && grid[i][j - 1] == 1)
                        perimeter -= 1;

                    // Check if it's connected to the Right
                    if(j < COLS - 1 && grid[i][j + 1] == 1)
                        perimeter -= 1;
                }
            }
        }

        return perimeter;
    }
};
