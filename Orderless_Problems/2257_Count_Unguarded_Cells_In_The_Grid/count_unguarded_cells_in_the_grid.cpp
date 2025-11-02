/*
    ==============
    === MEDIUM ===
    ==============

    =======================================
    2257) Count Unguarded Cells in the Grid
    =======================================

    ============
    Description:
    ============

    You are given two integers m and n representing a 0-indexed m x n grid. You
    are also given two 2D integer arrays guards and walls where guards[i] =
    [rowi, coli] and walls[j] = [rowj, colj] represent the positions of the ith
    guard and jth wall respectively.

    A guard can see every cell in the four cardinal directions (north, east,
    south, or west) starting from their position unless obstructed by a wall or
    another guard. A cell is guarded if there is at least one guard that can
    see it.

    Return the number of unoccupied cells that are not guarded.

    ====================================================================================================
    FUNCTION: int countUnguarded(int m, int n, vector<vector<int>>& guards, vector<vector<int>>& walls);
    ====================================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: m = 4, n = 6, guards = [[0,0],[1,1],[2,3]], walls = [[0,1],[2,2],[1,4]]
    Output: 7
    Explanation: The guarded and unguarded cells are shown in red and green
    respectively in the above diagram. There are a total of 7 unguarded cells,
    so we return 7.


    --- Example 2 ---
    Input: m = 3, n = 3, guards = [[1,1]], walls = [[0,1],[1,0],[2,1],[1,2]]
    Output: 4
    Explanation: The unguarded cells are shown in green in the above diagram.
    There are a total of 4 unguarded cells, so we return 4.


    *** Constraints ***
    1 <= m, n <= 10^5
    2 <= m * n <= 10^5
    1 <= guards.length, walls.length <= 5 * 10^4
    2 <= guards.length + walls.length <= m * n
    guards[i].length == walls[j].length == 2
    0 <= rowi, rowj < m
    0 <= coli, colj < n
    All the positions in guards and walls are unique.

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Just a basic "Simulation" on the grid. We put all the guards(1s) and all
    the walls (2s) in the newly created "table" of size "m x n" and then we
    begin at each guard's position. We go in every direciton at the time.

    If we go out of bounds on any side OR we hit a wall OR (this is important)
    we stumble upon another Guard, we STOP.

    Why do we stop if we stubmel upon another guard?

    Because we do not want to do the same job twice. We know that once we get
    to that Guard(or maybe we've already been on that guard) we will(or already
    were) check all the cells in that direction from that Guard.

    There's no need to be repetitive.

    Example:
             0     1     2     3     4     5     6
          +-----+-----+-----+-----+-----+-----+-----+
        0 |     |     |     |     |     |     |     |
          +-----+-----+-----+-----+-----+-----+-----+
        1 |     |  G  |     |  G  |     |     |     |
          +-----+-----+-----+-----+-----+-----+-----+
        2 |     |     |     |     |     |     |     |
          +-----+-----+-----+-----+-----+-----+-----+
        4 |     |     |     |     |     |     |     |
          +-----+-----+-----+-----+-----+-----+-----+
        5 |     |  G  |     |     |  W  |     |     |
          +-----+-----+-----+-----+-----+-----+-----+
        6 |     |     |     |  W  |     |     |     |
          +-----+-----+-----+-----+-----+-----+-----+
        7 |     |     |     |     |     |     |     |
          +-----+-----+-----+-----+-----+-----+-----+

        Consider Guard at {1,1}. Once we start iterating to the right, we'll
        stumble upon a Guard at {1,3}. At that point do we really need to keep
        going until the end of the row?

        No, because that will be done once begin iterating from Guard at {1,3}.


        Similarly, if we begin iterating upwards, from Guard {5,1}, once we get
        to Guard at {1,1}, we do NOT have to keep going up since we've ALREADY
        done that job. We can stop here and be sure we've done the job already.
        (Since Guard at {1,1} was done BEFORE Guard at {5,1})


    Since table is of size "m x n", we subtract all the Guards and Walls'
    positions(they are unique, meaning Guards and Walls CANNOT be placed on the
    same cell) and then we subtract every cell that is SEEN.

    At the end we return "result" that has the correct number on UNGUARDED
    cells.

*/

/* Time  Beats: 53.67% */
/* Space Beats: 48.17% */

/* Time  Complexity: O(M * N) */
/* Space Complexity: O(M * N) */
class Solution {
public:
    int countUnguarded(int m, int n, vector<vector<int>>& guards, vector<vector<int>>& walls)
    {
        const int GUARDS_SIZE = guards.size();
        const int WALLS_SIZE  = walls.size();

        vector<vector<int>> grid(m, vector<int>(n, 0));

        for (int i = 0; i < GUARDS_SIZE; i++)
            grid[guards[i][0]][guards[i][1]] = 1;

        for (int i = 0; i < WALLS_SIZE; i++)
            grid[walls[i][0]][walls[i][1]] = 2;

        for (int row = 0; row < m; row++)
        {
            for (int col = 0; col < n; col++)
            {
                if (grid[row][col] == 1) // If it's a guard
                {
                    dfs(0, row-1, col  , grid); // Up
                    dfs(1, row+1, col  , grid); // Down
                    dfs(2, row  , col-1, grid); // Left
                    dfs(3, row  , col+1, grid); // Right
                }
            }
        }

        int result = 0;
        for (int row = 0; row < m; row++)
        {
            for (int col = 0; col < n; col++)
            {
                if (grid[row][col] == 0)
                    result++;
            }
        }

        return result;
    }

private:
    void dfs(int dir, int row, int col, vector<vector<int>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        if (row < 0 || col < 0 || row >= ROWS || col >= COLS)
            return;

        if (grid[row][col] == 1 || grid[row][col] == 2)
            return;

        grid[row][col] = 3; // Now it's a GUARDED cell

        switch (dir)
        {
            case 0: // Up
                dfs(0, row-1, col  , grid);
                break;

            case 1: // Down
                dfs(1, row+1, col  , grid);
                break;

            case 2: // Left
                dfs(2, row  , col-1, grid);
                break;

            case 3: // Right
                dfs(3, row  , col+1, grid);
                break;
        }
    }
};
