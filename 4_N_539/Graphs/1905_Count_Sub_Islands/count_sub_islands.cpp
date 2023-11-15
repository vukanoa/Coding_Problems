#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    1905) Count Sub Islands
    ===========================

    ============
    Description:
    ============

    You are given two m x n binary matrices grid1 and grid2 containing only 0's
    (representing water) and 1's (representing land). An island is a group of
    1's connected 4-directionally (horizontal or vertical). Any cells outside
    of the grid are considered water cells.

    An island in grid2 is considered a sub-island if there is an island in
    grid1 that contains all the cells that make up this island in grid2.

    Return the number of islands in grid2 that are considered sub-islands.

    ======================================================================================
    FUNCTION: int countSubIslands(vector<vector<int>>& grid1, vector<vector<int>>& grid2);
    ======================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: grid1 = [[1,1,1,0,0],
                    [0,1,1,1,1],
                    [0,0,0,0,0],
                    [1,0,0,0,0],
                    [1,1,0,1,1]],

            grid2 = [[1,1,1,0,0],
                     [0,0,1,1,1],
                     [0,1,0,0,0],
                     [1,0,1,1,0],
                     [0,1,0,1,0]]
    Output: 3
    Explanation: In the picture above, the grid on the left is grid1 and the
    grid on the right is grid2.  The 1s colored red in grid2 are those
    considered to be part of a sub-island. There are three sub-islands.


    --- Example 2 ---
    Input: grid1 = [[1,0,1,0,1],
                    [1,1,1,1,1],
                    [0,0,0,0,0],
                    [1,1,1,1,1],
                    [1,0,1,0,1]],

            grid2 = [[0,0,0,0,0],
                     [1,1,1,1,1],
                     [0,1,0,1,0],
                     [0,1,0,1,0],
                     [1,0,0,0,1]]
    Output: 2
    Explanation: In the picture above, the grid on the left is grid1 and the
    grid on the right is grid2.  The 1s colored red in grid2 are those
    considered to be part of a sub-island. There are two sub-islands.


    *** Constraints ***
    m == grid1.length == grid2.length
    n == grid1[i].length == grid2[i].length
    1 <= m, n <= 500
    grid1[i][j] and grid2[i][j] are either 0 or 1.

*/

/*
    ------------
    --- IDEA ---
    ------------

    Similar to "Number of Islands", however it's important to note that if we
    ever find a field in grid2 that ISN'T present in grid1, we MUST soak all
    connected fields, i.e. that entire island in grid2.

    That is the crux of this problem.

*/

/* Time  Beats: 84.07% */
/* Space Beats: 83.00% */

/* Time  Complexity: O(M * N * 4^(M * N)) */
/* Space Complexity: O(M * N) */
class Solution_Verbose {
public:
    int countSubIslands(std::vector<std::vector<int>>& grid1, std::vector<std::vector<int>>& grid2)
    {
        const int ROWS = grid1.size();
        const int COLS = grid1[0].size();

        int sub_islands = 0;

        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLS; j++)
            {
                if (grid2[i][j] == 1 && grid2[i][j] == grid1[i][j])
                    sub_islands += dfs(grid1, grid2, i, j) ? 1 : 0;
            }
        }

        return sub_islands;
    }

private:
    bool dfs(std::vector<std::vector<int>>& grid1, std::vector<std::vector<int>>& grid2, int i, int j)
    {
        const int ROWS = grid1.size();
        const int COLS = grid1[0].size();

        if (i < 0 || j < 0 || i == ROWS || j == COLS || grid2[i][j] != 1)
            return true;

        if (grid2[i][j] == 1 && grid1[i][j] == 0)
            return false;

        grid2[i][j] = 2;

        /* Signing Cross */
        if (!dfs(grid1, grid2, i-1, j  )) { grid2[i][j] = 1; soak(grid1, grid2, i, j); return false; } // Up
        if (!dfs(grid1, grid2, i+1, j  )) { grid2[i][j] = 1; soak(grid1, grid2, i, j); return false; } // Down
        if (!dfs(grid1, grid2, i  , j-1)) { grid2[i][j] = 1; soak(grid1, grid2, i, j); return false; } // Left
        if (!dfs(grid1, grid2, i  , j+1)) { grid2[i][j] = 1; soak(grid1, grid2, i, j); return false; } // Right

        return true;
    }

    void soak(std::vector<std::vector<int>>& grid1, std::vector<std::vector<int>>& grid2, int i, int j)
    {
        const int ROWS = grid1.size();
        const int COLS = grid1[0].size();

        if (i < 0 || j < 0 || i == ROWS || j == COLS || grid2[i][j] != 1)
            return;

        grid2[i][j] = 2;

        /* Signing Cross */
        soak(grid1, grid2, i-1, j  );
        soak(grid1, grid2, i+1, j  );
        soak(grid1, grid2, i  , j-1);
        soak(grid1, grid2, i  , j+1);
    }
};
