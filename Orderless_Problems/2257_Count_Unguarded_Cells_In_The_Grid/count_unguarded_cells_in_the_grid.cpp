#include <iostream>
#include <vector>

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

/* Time  Beats: 81.44% */
/* Space Beats: 88.24% */

/* Time  Complexity: O(guards.size() * (m + n)) */
/* Space Complexity: O(m + n)                   */
class Solution {
public:
    int countUnguarded(int m, int n, vector<vector<int>>& guards, vector<vector<int>>& walls)
    {
        if ( (guards.size() + walls.size()) == m * n )
            return 0;

        vector<vector<int>> table(m, vector(n, 0)); // size, initial value

        for (int i = 0; i < guards.size(); i++)
            table[guards[i][0]][guards[i][1]] = 1;

        for (int j = 0; j < walls.size(); j++)
            table[walls[j][0]][walls[j][1]] = 2;

        int result = m * n - guards.size() - walls.size();
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (table[i][j] == 1)
                {
                    // Signing cross
                    direction('u', table, m, n, result, i-1, j  );
                    direction('d', table, m, n, result, i+1, j  );
                    direction('l', table, m, n, result, i  , j-1);
                    direction('r', table, m, n, result, i  , j+1);
                }
            }
        }

        return result;
    }

private:
    void direction(char dir, vector<vector<int>>& table, int& m, int &n, int& result, int i, int j)
    {
        if (i < 0 || j < 0 || i == m || j == n || table[i][j] == 1 || table[i][j] == 2)
            return;

        if (table[i][j] == 0)
        {
            table[i][j] = 3; // Guarded-cell
            result--;
        }

        switch (dir)
        {
            case 'u':
                direction('u', table, m, n, result, i-1, j  );
                break;

            case 'd':
                direction('d', table, m, n, result, i+1, j  );
                break;

            case 'l':
                direction('l', table, m, n, result, i  , j-1);
                break;

            case 'r':
                direction('r', table, m, n, result, i  , j+1);
                break;
        }
    }
};
