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

#include <vector>
using namespace std;

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
class Solution_DFS_Marking_Input_Grid {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();
        int result = 0;

        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                if (grid[row][col] == 1)
                {
                    int area = 0;
                    dfs(row, col, area, grid);

                    result = max(result, area);
                }
            }
        }

        return result;
    }

private:
    void dfs(int row, int col, int& area, vector<vector<int>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        if (row < 0 || col < 0 || row == ROWS || col == COLS)
            return;

        if (grid[row][col] != 1)
            return;

        area++;
        grid[row][col] = 2; // Don't traverse it twice. Mark as traversed.

        /* Signing Cross */
        dfs(row-1, col  , area, grid); // Up
        dfs(row+1, col  , area, grid); // Down
        dfs(row  , col-1, area, grid); // Left
        dfs(row  , col+1, area, grid); // Right
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This one is the same as above, however it uses "visited" vector instead of
    marking the grid itself.

    But why did I, then, include both Solutions?

    Because maybe it's not allowed to change the Input. Also the "grid" is
    passed by the reference, therefore any change to it will result in the
    change of the original Input.

    We could do another DFS to re-mark all the 2s back into 1s, however that
    would be LESS efficient that doing it with this "visited" vector.

    It's generally good to see and be aware of both solutions, especially if
    you're a beginner.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  57.49% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(ROWS * COLS) */
class Solution_DFS_Using_Visited {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();
        int result = 0;

        vector<vector<bool>> visited(ROWS, vector<bool>(COLS, false));

        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                if (grid[row][col] == 1 && ! visited[row][col])
                {
                    int area = 0;
                    dfs(row, col, visited, grid, area);

                    result = max(result, area);
                }
            }
        }

        return result;
    }

private:
    void dfs(int row, int col, vector<vector<bool>>& visited, vector<vector<int>>& grid, int& area)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        if (row < 0 || col < 0 || row >= ROWS || col >= COLS)
            return;

        if (visited[row][col] || grid[row][col] == 0)
            return;

        visited[row][col] = true;
        area++;

        dfs(row-1, col  , visited, grid, area);
        dfs(row+1, col  , visited, grid, area);
        dfs(row  , col-1, visited, grid, area);
        dfs(row  , col+1, visited, grid, area);
    }
};
