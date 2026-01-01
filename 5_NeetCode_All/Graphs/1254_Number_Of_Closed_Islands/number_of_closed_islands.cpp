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

    Anytime you find an "Open Island", mark it(by changing it from 0 to 2)

    So what is, in this problem, an "Open Island"?
    An "Open Island" is a land that is connected to the edge(directly or
    indirectly) in at least one of the 4 directions.


    Example:

        (This is a MODIFIED Example 1)
        Input: grid = [[1,1,1,1,1,1,1,0],
                       [1,0,0,0,1,0,0,0],
                       [1,0,1,0,1,1,1,0],
                       [1,0,0,0,0,1,0,1],
                       [1,1,1,1,1,1,1,0]]


        +-----+-----+-----+-----+-----+-----+-----+-----+
        |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  0  | <-------
        +-----+-----+-----+-----+-----+-----+-----+-----+        |
        |  1  |  0  |  0  |  0  |  1  |  0  |  0  |  0  | <-------
        +-----+-----+-----+-----+-----+-----+-----+-----+        |
        |  1  |  0  |  1  |  0  |  1  |  1  |  1  |  0  | <-------
        +-----+-----+-----+-----+-----+-----+-----+-----+        |
        |  1  |  0  |  0  |  0  |  0  |  1  |  0  |  1  |        |
        +-----+-----+-----+-----+-----+-----+-----+-----+        |
        |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  0  | <-------
        +-----+-----+-----+-----+-----+-----+-----+-----+        |
                                                                 |
                                                                 |
                                                                 |
                                      ___________________________|
                                      |
                                      |
                                      |
        In the above ASCII drawing, these cells are DIRECTLY connected to the
        edge in at least one of the 4 directions.

        On the other hand, cells at indices: [1,5], [1,6] are INDIRECTLY
        connected to the edge in at least one of the 4 directions.

        For example Land at cells [1,5] is connected to [1,6] which is
        connected to cell at index [1,7] which is DIRECTLY connected to the
        edge on its right. Therefore, we say that both [1,5] and [1,6] are
        also connected to the edge.


    Therefore, traverse:
        All the Rows    in First and Last Columns
        All the Columns in First and Last Rows

    and mark every Land that is connected to one or more edges(directly or
    undirectly) in at least one of the 4 directions.

    After that, iterate through entire grid, cell by cell, and each time you
    stumble on some Land(designeated by 0), perform a DFS in which you will,
    again, mark all the Land with value 2.

    The number of performed DFSs is the number of "Closed Islands".

    At the end, if you want you can restore the original grid by changing all
    the 2's back to 0's.
    (You DON'T have to. It's optional)

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

        /* ************************************************************* */
        /* *** Mark all land fields connected to the edge in any way *** */
        /* ************************************************************* */

        /* Iterate through all the Rows in First and Last Column */
        for (int i = 0; i < ROWS; i++)
        {
            if (grid[i][0] == 0)
                dfs(grid, i, 0);

            if (grid[i][COLS-1] == 0)
                dfs(grid, i, COLS-1);
        }

        /* Iterate through all the Columns in First and Last Row */
        for (int j = 0; j < COLS; j++)
        {
            if (grid[0][j] == 0)
                dfs(grid, 0, j);

            if (grid[ROWS-1][j] == 0)
                dfs(grid, ROWS-1, j);
        }

        int islands = 0;

        /* Count Islands by counting the amount of performed DFSs */
        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLS; j++)
            {
                if (grid[i][j] == 0)
                {
                    islands++;
                    dfs(grid, i, j);
                }
            }
        }

        /* Restore grid matrix back to Original(Not obligatory!) */
        // for (int i = 0; i < ROWS; i++)
        // {
        //     for (int j = 0; j < COLS; j++)
        //     {
        //         if (grid[i][j] == 2)
        //             grid[i][j] = 0;
        //     }
        // }

        return islands;
    }

private:
    void dfs(std::vector<std::vector<int>>& grid, int i, int j)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        if (i < 0 || j < 0 || i == ROWS || j == COLS || grid[i][j] != 0)
            return;

        grid[i][j] = 2;

        dfs(grid, i-1, j  );
        dfs(grid, i+1, j  );
        dfs(grid, i  , j-1);
        dfs(grid, i  , j+1);
    }
};
