#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    1020) Number of Enclaves
    ===========================

    ============
    Description:
    ============

    You are given an m x n binary matrix grid, where 0 represents a sea cell
    and 1 represents a land cell.

    A move consists of walking from one land cell to another adjacent
    (4-directionally) land cell or walking off the boundary of the grid.

    Return the number of land cells in grid for which we cannot walk off the
    boundary of the grid in any number of moves.

    =====================================================
    FUNCTION: int numEnclaves(vector<vector<int>>& grid);
    =====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    +-----+-----+-----+-----+
    |  0  |  0  |  0  |  0  |
    +-----+-----+-----+-----+
    |  1  |  0  |  1  |  0  |
    +-----+-----+-----+-----+
    |  0  |  1  |  1  |  0  |
    +-----+-----+-----+-----+
    |  0  |  0  |  0  |  0  |
    +-----+-----+-----+-----+

    Input: grid = [[0,0,0,0],[1,0,1,0],[0,1,1,0],[0,0,0,0]]
    Output: 3
    Explanation: There are three 1s that are enclosed by 0s, and one 1 that is
                 not enclosed because its on the boundary.


    --- Example 2 ---
    +-----+-----+-----+-----+
    |  0  |  1  |  1  |  0  |
    +-----+-----+-----+-----+
    |  0  |  0  |  1  |  0  |
    +-----+-----+-----+-----+
    |  0  |  0  |  1  |  0  |
    +-----+-----+-----+-----+
    |  0  |  0  |  0  |  0  |
    +-----+-----+-----+-----+
    Input: grid = [[0,1,1,0],[0,0,1,0],[0,0,1,0],[0,0,0,0]]
    Output: 0
    Explanation: All 1s are either on the boundary or can reach the boundary.


    *** Constraints ***
    m == grid.length
    n == grid[i].length
    1 <= m, n <= 500
    grid[i][j] is either 0 or 1.

*/

/*
    ------------
    --- IDEA ---
    ------------

    Think of in reverse.

    (It is almost an equivalent problem to LC: 1254_Number_Of_Closed_Islands,
     although this is a slightly easier one because if doesn't perform a DFS in
     the last part of the implementation, i.e. in Nested Loops)

    Only check if there is land on the edges, i.e. in:
        1. 0-th column
        2. last column
        3. 0th-row
        4. last row

    If you find any land in these 4 "arrays", try to follow those lands, i.e.
    try to mark all the land, 4-directionally connected to it, as "visited".
    For example designate all such land with a number 2.

    Number 2 now indicates that the land in the "middle" of a grid is INDEED
    connected to the edges, i.e. it doesn't fulfill the property:

    "Return the number of land cells in grid for which we cannot walk off the
    boundary of the grid in any number of moves."

    After we've done this to all 4 "arrays", meaning:
        1. 0-th column
        2. last column
        3. 0th-row
        4. last row

    We can then traverse the "middle" portion of the grid, i.e.
        i in [1, ROWS-2] and
        j in [1, COLS-2].

    And simply count 1's. Since we've "marked" all the land in the "middle"
    that doesn't fulfill our needs, with number 2, now we can simply count the
    land in the middle that has the value of 1.

    That's it.

    Make sure to understand that we won't visit a cell more than twice, thus
    making this O(2 * ROWS * COLS) which is just O(ROWS * COLS) i.e. O(M * N).

*/

/* Time  Beats: 94.55% */
/* Space Beats: 50.58% */

/* Time  Complexity: O(m * n) */ // We will only access each cell at max twice
/* Space Complexity: O(m * n) */
class Solution {
public:
    int numEnclaves(std::vector<std::vector<int>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();
        int enclaves = 0;

        /* Traverse all the Rows in 0-th and Last Column */
        for (int i = 0; i < ROWS; i++)
        {
            if (grid[i][0] == 1)
                dfs(grid, i, 0);

            if (grid[i][COLS-1] == 1)
                dfs(grid, i, COLS-1);
        }

        /* Traverse all the Columns in 0-th and Last Row */
        for (int j = 0; j < COLS; j++)
        {
            if (grid[0][j] == 1)
                dfs(grid, 0, j);

            if (grid[ROWS-1][j] == 1)
                dfs(grid, ROWS-1, j);
        }

        /* Count Enclaves */
        for (int i = 1; i < ROWS-1; i++)
        {
            for (int j = 1; j < COLS-1; j++)
            {
                if (grid[i][j] == 1)
                    enclaves++;
            }
        }

        return enclaves;
    }

private:
    void dfs(std::vector<std::vector<int>>& grid, int i, int j)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        if (i < 0 || j < 0 || i == ROWS || j == COLS || grid[i][j] != 1)
            return;

        grid[i][j] = 2;

        /* Singing Cross */
        dfs(grid, i-1, j  );
        dfs(grid, i+1, j  );
        dfs(grid, i  , j-1);
        dfs(grid, i  , j+1);
    }
};
