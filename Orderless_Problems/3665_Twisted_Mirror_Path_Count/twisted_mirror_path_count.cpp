/*
    ==============
    === MEDIUM ===
    ==============

    ===============================
    3665) Twisted Mirror Path Count
    ===============================

    ============
    Description:
    ============

    Given an m x n binary grid grid where:

        + grid[i][j] == 0 represents an empty cell, and
        + grid[i][j] == 1 represents a mirror.

    A robot starts at the top-left corner of the grid (0, 0) and wants to
    reach the bottom-right corner (m - 1, n - 1). It can move only right or
    down. If the robot attempts to move into a mirror cell, it is reflected
    before entering that cell:

        + If it tries to move right into a mirror, it is turned down and moved
          into the cell directly below the mirror.

        + If it tries to move down into a mirror, it is turned right and moved
          into the cell directly to the right of the mirror.

    If this reflection would cause the robot to move outside the grid
    boundaries, the path is considered invalid and should not be counted.

    Return the number of unique valid paths from (0, 0) to (m - 1, n - 1).

    Since the answer may be very large, return it modulo 109 + 7.

    =====
    Note: If a reflection moves the robot into a mirror cell, the robot is
          immediately reflected again based on the direction it used to enter
          that mirror: if it entered while moving right, it will be turned
          down; if it entered while moving down, it will be turned right. This
          process will continue until either the last cell is reached, the
          robot moves out of bounds or the robot moves to a non-mirror cell.
    =====

    =====================================================
    FUNCTION: int uniquePaths(vector<vector<int>>& grid);
    =====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: grid = [[0,1,0],[0,0,1],[1,0,0]]
    Output: 5
    Explanation:
    Number    Full Path
    1         (0, 0) --> (0, 1) [M] --> (1, 1)     -->  (1, 2) [M] --> (2, 2)
    2         (0, 0) --> (0, 1) [M] --> (1, 1)     -->  (2, 1)     --> (2, 2)
    3         (0, 0) --> (1, 0)     --> (1, 1)     -->  (1, 2) [M] --> (2, 2)
    4         (0, 0) --> (1, 0)     --> (1, 1)     -->  (2, 1)     --> (2, 2)
    5         (0, 0) --> (1, 0)     --> (2, 0) [M] -->  (2, 1)     --> (2, 2)

    + [M] indicates the robot attempted to enter a mirror cell and instead
      reflected.



    --- Example 2 ---
    Input: grid = [[0,0],[0,0]]
    Output: 2
    Explanation:
    Number    Full Path
    1         (0, 0) --> (0, 1) --> (1, 1)
    2         (0, 0) --> (1, 0) --> (1, 1)



    --- Example 3 ---
    Input: grid = [[0,1,1],[1,1,0]]
    Output: 1
    Explanation:
    Number    Full Path
    1    (0, 0) --> (0, 1) [M] --> (1, 1) [M] --> (1, 2)

    (0, 0) --> (1, 0) [M] --> (1, 1) [M] --> (2, 1) goes out of bounds, so it
    is invalid.



    *** Constraints ***
    m == grid.length
    n == grid[i].length
    2 <= m, n <= 500
    grid[i][j] is either 0 or 1.
    grid[0][0] == grid[m - 1][n - 1] == 0

*/

#include <cstring>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Standard Memoization.

*/

/* Time  Beats: -% */
/* Space Beats: 100.00% */

/* Time  Complexity: O(ROWS * COLS * 2) --> (ROWS * COLS) */
/* Space Complexity: O(ROWS * COLS * 2) --> (ROWS * COLS) */
class Solution_Memoization {
private:
    const int MOD = 1e9 + 7;
    int memo[501][501][2];

public:
    int uniquePaths(vector<vector<int>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        /* Memset */
        memset(memo, -1, sizeof(memo));

        return (solve(1, 0, 0, grid) + solve (0, 1, 1, grid)) % MOD;
    }

private:
    int solve(int row, int col, int came_from, vector<vector<int>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        if (row < 0 || col < 0 || row >= ROWS || col >= COLS)
            return 0;

        if (row == ROWS-1 && col == COLS-1)
            return 1;

        if (memo[row][col][came_from] != -1)
            return memo[row][col][came_from];

        int go_down  = 0;
        int go_right = 0;

        if (grid[row][col] == 1) // Mirror
        {
            if (came_from == 0) // Came from ABOVE
            {
                go_right = solve(row , col+1, 1, grid);
            }
            else // came_from == 1 // Came from LEFT
            {
                go_down = solve(row+1, col  , 0, grid);
            }
        }
        else // NOT a Mirror
        {
            go_down  = solve(row+1, col   , 0, grid);
            go_right = solve(row  , col+1 , 1, grid);
        }

        return memo[row][col][came_from] = (go_down + go_right) % MOD;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same idea, but implemented using "Tabulation", i.e. "Bottom-Up" approach.

*/

/* Time  Complexity: O(ROWS * COLS * 2) --> (ROWS * COLS) */
/* Space Complexity: O(ROWS * COLS * 2) --> (ROWS * COLS) */
class Solution_Tabulation__Bottom_Up {
private:
    const int MOD = 1e9 + 7;

public:
    int uniquePaths(vector<vector<int>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        const int ZERO_ROW = 0;
        const int ZERO_COL = 0;

        const int CAME_FROM_ABOVE = 0;
        const int CAME_FROM_LEFT  = 1;


        vector<vector<vector<long long>>> dp(ROWS, vector<vector<long long>>(COLS, vector<long long>(2, 0LL)));
        dp[ZERO_ROW][ZERO_COL] = {1LL, 1LL};

        // Do Zeroeth row
        for (int row = 1; row < ROWS; row++)
        {
            if (grid[row-1][ZERO_COL] == 1) // Mirror
                dp[row][ZERO_COL][CAME_FROM_ABOVE] = dp[row-1][ZERO_COL][CAME_FROM_LEFT];
            else
                dp[row][ZERO_COL][CAME_FROM_ABOVE] = dp[row-1][ZERO_COL][CAME_FROM_ABOVE];
        }


        // Do Zeroeth col
        for (int col = 1; col < COLS; col++)
        {
            if (grid[ZERO_ROW][col-1] == 1) // Mirror
                dp[ZERO_ROW][col][CAME_FROM_LEFT] = dp[ZERO_ROW][col-1][CAME_FROM_ABOVE];
            else
                dp[ZERO_ROW][col][CAME_FROM_LEFT] = dp[ZERO_ROW][col-1][CAME_FROM_LEFT];
        }


        // Do a Bottom-Up Dynamic Programming
        for (int row = 1; row < ROWS; row++)
        {
            for (int col = 1; col < COLS; col++)
            {
                // Above
                if (grid[row-1][col] == 1) // Mirror
                {
                    dp[row][col][CAME_FROM_ABOVE] = dp[row-1][col][CAME_FROM_LEFT];
                }
                else
                {
                    dp[row][col][CAME_FROM_ABOVE] = dp[row-1][col][CAME_FROM_LEFT] +
                                                    dp[row-1][col][CAME_FROM_ABOVE];

                    dp[row][col][CAME_FROM_ABOVE] %= MOD;
                }


                // Left
                if (grid[row][col-1] == 1) // Mirror
                {
                    dp[row][col][CAME_FROM_LEFT] = dp[row-1][col][CAME_FROM_ABOVE];
                }
                else
                {
                    dp[row][col][CAME_FROM_LEFT] = dp[row][col-1][CAME_FROM_LEFT] +
                                                   dp[row][col-1][CAME_FROM_ABOVE];

                    dp[row][col][CAME_FROM_LEFT] %= MOD;
                }
            }
        }

        return (dp[ROWS-1][COLS-1][CAME_FROM_ABOVE] +
                dp[ROWS-1][COLS-1][CAME_FROM_LEFT]) % MOD;
    }
};
