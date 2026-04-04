/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    286) Walls and Gates
    ===========================

    ============
    Description:
    ============

    You are given a m x n 2D grid initialized with these three possible values.

        1. -1 - A wall or an obstacle.
        2. 0 - A gate.
        3. INF - Infinity means an empty room. We use the value 231 - 1 =
           2147483647 to represent INF as you may assume that the distance to a
           gate is less than 2147483647.

    Fill each empty room with the distance to its nearest gate. If it is
    impossible to reach a gate, it should be filled with INF.

    ========================================================================
    FUNCTION: vector<vector<int>> wallsAndGates(vector<vector<int>>& rooms);
    ========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
        INF  -1  0  INF
        INF INF INF  -1
        INF  -1 INF  -1
          0  -1 INF INF

    Input:  [[INF, -1, 0, INF], [INF, INF, INF, -1], [INF, -1, INF, -1],
             [0, -1, INF, INF]]

    Output: [[3, -1, 0, 1], [2, 2, 1, -1], [1, -1, 2, -1], [0, -1, 3, 4]]

        3  -1   0   1
        2   2   1  -1
        1  -1   2  -1
        0  -1   3   4

    *** Constraints ***
    <Unknown>

*/

#include <climits>
#include <vector>
#include <queue>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Fundamental "Multi-source BFS" technique.

*/

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(ROWS * COLS) */
class Solution_Multi_Source_BFS {
public:
   void islandsAndTreasure(vector<vector<int>>& grid)
   {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        queue<pair<int,int>> queue;

        /* Initialize Queue */
        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                if (grid[row][col] == 0)
                    queue.push( {row, col} );
            }
        }

        /* Signing Cross */
        vector<pair<int, int>> directions = {{-1,0}, {1,0}, {0,-1}, {0,1}};

        /* Multi-source BFS */
        while ( ! queue.empty())
        {
            auto [row, col] = queue.front();
            queue.pop();

            int curr_distance = grid[row][col];

            for (const auto& dir : directions)
            {
                int new_row = row + dir.first;
                int new_col = col + dir.second;

                if (new_row < 0 || new_col < 0 || new_row >= ROWS || new_col >= COLS)
                    continue;

                if (grid[new_row][new_col] != INT_MAX)
                    continue;

                grid[new_row][new_col] = curr_distance + 1;
                queue.push( {new_row, new_col} );
            }
        }
    }
};
