/*
    ============
    === HARD ===
    ============

    ============================================
    4046) Minimum Cost Path With At Most K Turns
    ============================================

    ============
    Description:
    ============

    You are given a 2D integer array grid of size m x n, where grid[i][j]
    represents the cost of visiting cell (i, j), and an integer k.

    You start at the top-left cell (0, 0) and want to reach the bottom-right
    cell (m - 1, n - 1).

    From each cell, you may move one step in any of the four directions: up,
    down, left, or right.

    The cost of a path is the sum of the values of all visited cells, including
    the starting and ending cells. If a cell is visited more than once, its
    value is included each time it is visited.

    Return the minimum possible path cost to reach (m - 1, n - 1) using at most
    k turns. If no such path exists, return -1.

    A turn occurs when the direction changes between two consecutive moves. For
    example, moving right and then down counts as one turn, while moving right
    and then right does not.

    ========================================================
    FUNCTION: int minCost(vector<vector<int>>& grid, int k);
    ========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: grid = [[2,7,3],[1,4,5]], k = 1
    Output: 12
    Explanation:
        An optimal path is (0, 0) → (1, 0) → (1, 1) → (1, 2). The moves are down, right, right.
        The direction changes from down to right once, so the path uses exactly k = 1 turn.
        The total path cost is 2 + 1 + 4 + 5 = 12.

    --- Example 2 ---
    Input: grid = [[4,1,9],[3,2,5],[4,8,6]], k = 2
    Output: 20
    Explanation:
        An optimal path is (0, 0) → (1, 0) → (1, 1) → (1, 2) → (2, 2). The moves are down, right, right, down.
        The direction changes from down to right and from right to down, so the path uses exactly k = 2 turns.
        The total path cost is 4 + 3 + 2 + 5 + 6 = 20.

    --- Example 3 ---
    Input: grid = [[1,9],[3,4]], k = 0
    Output: -1
    Explanation:
        It is impossible to reach (1, 1) using k = 0 turns. Thus, the answer is -1.


    *** Constraints ***
    1 <= m == grid.length <= 75
    1 <= n == grid[i].length <= 75
    0 <= grid[i][j] <= 1000
    0 <= k < min(m, n)

*/

#include <vector>
using namespace std;


/* Time  Beats: 98.56% */
/* Space Beats: 90.85% */

/* Time  Complexity: O(ROWS * COLS * K) */
/* Space Complexity: O(ROWS * COLS * K) */
class Solution {
public:
    int minCost(vector<vector<int>>& grid, int k)
    {
        const long long INF = 1LL * 1e15;

        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        if (ROWS == 1 && COLS == 1)
            return grid[0][0];


        vector<vector<long long>> dp(ROWS, vector<long long>(COLS, INF));
        dp[0][0] = grid[0][0];

        for (int used_turns = 0; used_turns <= k; used_turns++)
        {
            vector<vector<long long>> next(ROWS, vector<long long>(COLS, INF));

            /* RIGHT */
            for (int row = 0; row < ROWS; row++)
            {
                long long min_cost = INF;

                for (int col = 1; col < COLS; col++)
                {
                    min_cost       = min(min_cost, dp  [row][col-1]) + grid[row][col];
                    next[row][col] = min(min_cost, next[row][col  ]);
                }
            }

            /* LEFT */
            for (int row = 0; row < ROWS; row++)
            {
                long long min_cost = INF;

                for (int col = COLS-2; col >= 0; col--)
                {
                    min_cost       = min(min_cost, dp  [row][col+1]) + grid[row][col];
                    next[row][col] = min(min_cost, next[row][col  ]);
                }
            }

            /* DOWN */
            for (int col = 0; col < COLS; col++)
            {
                long long min_cost = INF;

                for (int row = 1; row < ROWS; row++)
                {
                    min_cost       = min(min_cost, dp  [row-1][col]) + grid[row][col];
                    next[row][col] = min(min_cost, next[row  ][col]);
                }
            }

            /* UP */
            for (int col = 0; col < COLS; col++)
            {
                long long min_cost = INF;

                for (int row = ROWS-2; row >= 0; row--)
                {
                    min_cost       = min(min_cost, dp  [row+1][col]) + grid[row][col];
                    next[row][col] = min(min_cost, next[row  ][col]);
                }
            }

            dp = std::move(next);
        }


        if (dp[ROWS-1][COLS-1] >= INF)
            return -1;

        return static_cast<int>(dp[ROWS-1][COLS-1]);
    }
};
