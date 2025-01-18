/*
    ============
    === HARD ===
    ============

    ============================================================
    1368) Minimum Cost to Make at Least One Valid Path in a Grid
    ============================================================

    ============
    Description:
    ============

    Given an m x n grid. Each cell of the grid has a sign pointing to the next
    cell you should visit if you are currently in this cell. The sign of
    grid[i][j] can be:

        1 which means go to the cell to the right. (i.e go from grid[i][j] to grid[i][j + 1])
        2 which means go to the cell to the left. (i.e go from grid[i][j] to grid[i][j - 1])
        3 which means go to the lower cell. (i.e go from grid[i][j] to grid[i + 1][j])
        4 which means go to the upper cell. (i.e go from grid[i][j] to grid[i - 1][j])

    Notice that there could be some signs on the cells of the grid that point
    outside the grid.

    You will initially start at the upper left cell (0, 0). A valid path in the
    grid is a path that starts from the upper left cell (0, 0) and ends at the
    bottom-right cell (m - 1, n - 1) following the signs on the grid. The valid
    path does not have to be the shortest.

    You can modify the sign on a cell with cost = 1. You can modify the sign on
    a cell one time only.

    Return the minimum cost to make the grid have at least one valid path.

    =================================================
    FUNCTION: int minCost(vector<vector<int>>& grid);
    =================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: grid = [[1,1,1,1],[2,2,2,2],[1,1,1,1],[2,2,2,2]]
    Output: 3
    Explanation: You will start at point (0, 0).
    The path to (3, 3) is as follows. (0, 0) --> (0, 1) --> (0, 2) --> (0, 3) change the arrow to down with cost = 1 --> (1, 3) --> (1, 2) --> (1, 1) --> (1, 0) change the arrow to down with cost = 1 --> (2, 0) --> (2, 1) --> (2, 2) --> (2, 3) change the arrow to down with cost = 1 --> (3, 3)
    The total cost = 3.


    --- Example 2 ---
    Input: grid = [[1,1,3],[3,2,2],[1,1,4]]
    Output: 0
    Explanation: You can follow the path from (0, 0) to (2, 2).


    --- Example 3 ---
    Input: grid = [[1,2],[4,3]]
    Output: 1


    *** Constraints ***
    m == grid.length
    n == grid[i].length
    1 <= m, n <= 100
    1 <= grid[i][j] <= 4

*/

#include <climits>
#include <queue>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 39.24% */
/* Space Beats: 30.10% */

/* Time  Complexity: O((ROWS * COLS)^2) */
/* Space Complexity: O(ROWS * COLS)     */
class Solution {
public:
    int minCost(vector<vector<int>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        vector<vector<int>> dp(ROWS, vector<int>(COLS, INT_MAX));
        dp[0][0] = 0;

        while (true)
        {
            // Store previous state to check for convergence
            vector<vector<int>> prev_state = dp;

            // Forward pass: check cells coming from left and top
            for (int row = 0; row < ROWS; row++)
            {
                for (int col = 0; col < COLS; col++)
                {
                    // Check cell above
                    if (row > 0)
                    {
                        dp[row][col] = min(dp[row][col],
                                           dp[row-1][col] + (grid[row-1][col] == 3 ? 0 : 1));
                    }

                    // Check cell to the left
                    if (col > 0)
                    {
                        dp[row][col] = min(dp[row][col],
                                           dp[row][col-1] + (grid[row][col-1] == 1 ? 0 : 1));
                    }
                }
            }

            // Backward pass: check cells coming from right and bottom
            for (int row = ROWS-1; row >= 0; row--)
            {
                for (int col = COLS-1; col >= 0; col--)
                {
                    // Check cell below
                    if (row < ROWS-1)
                    {
                        dp[row][col] = min(dp[row][col],
                                           dp[row+1][col] + (grid[row+1][col] == 4 ? 0 : 1));
                    }

                    // Check cell to the right
                    if (col < COLS-1)
                    {
                        dp[row][col] = min(dp[row][col],
                                           dp[row][col+1] + (grid[row][col+1] == 2 ? 0 : 1));
                    }
                }
            }

            // If no changes were made in this iteration, we've found optimal
            // solution
            if (prev_state == dp)
                break;
        }

        return dp[ROWS-1][COLS-1];
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 24.33% */
/* Space Beats: 23.91% */

/* Time  Complexity: O(ROWS * COLS * log(ROWS * COLS)) */
/* Space Complexity: O(ROWS * COLS)                    */
class Solution_Dijkstra {
public:
    // Direction vectors: right, left, down, up (matching grid values 1, 2, 3, 4)
    vector<vector<int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    int minCost(vector<vector<int>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        // Min-heap ordered by cost. Each element is {cost, row, col}
        priority_queue<vector<int>, vector<vector<int>>, greater<>> min_heap;
        min_heap.push({0, 0, 0});

        // Track minimum cost to reach each cell
        vector<vector<int>> min_cost(ROWS, vector<int>(COLS, INT_MAX));
        min_cost[0][0] = 0;

        while ( ! min_heap.empty())
        {
            auto curr = min_heap.top();
            min_heap.pop();

            int cost = curr[0];
            int row  = curr[1];
            int col  = curr[2];

            // Skip if we've found a better path to this cell
            if (min_cost[row][col] != cost)
                continue;

            for (int dir = 0; dir < 4; dir++)
            {
                int new_row = row + directions[dir][0];
                int new_col = col + directions[dir][1];

                // Check if new position is valid
                if (new_row >= 0 && new_col >= 0 && new_row < ROWS && new_col < COLS)
                {
                    // Add cost=1 if we need to change direction
                    int new_cost = cost + (dir != (grid[row][col] - 1) ? 1 : 0);

                    // Update if we found a better path
                    if (min_cost[new_row][new_col] > new_cost)
                    {
                        min_cost[new_row][new_col] = new_cost;
                        min_heap.push( {new_cost, new_row, new_col} );
                    }
                }
            }
        }

        return min_cost[ROWS-1][COLS-1];
    }
};
