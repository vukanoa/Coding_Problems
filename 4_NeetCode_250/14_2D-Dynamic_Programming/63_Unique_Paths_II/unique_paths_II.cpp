/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    63) Unique Paths II
    ===========================

    ============
    Description:
    ============

    You are given an m x n integer array grid. There is a robot initially
    located at the top-left corner (i.e., grid[0][0]). The robot tries to move
    to the bottom-right corner (i.e., grid[m - 1][n - 1]). The robot can only
    move either down or right at any point in time.

    An obstacle and space are marked as 1 or 0 respectively in grid. A path
    that the robot takes cannot include any square that is an obstacle.

    Return the number of possible unique paths that the robot can take to reach
    the bottom-right corner.

    The testcases are generated so that the answer will be less than or equal
    to 2 * 10^9.

    =========================================================================
    FUNCTION:int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid);
    =========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: obstacleGrid = [[0,0,0],[0,1,0],[0,0,0]]
    Output: 2
    Explanation: There is one obstacle in the middle of the 3x3 grid above.
    There are two ways to reach the bottom-right corner:
    1. Right -> Right -> Down -> Down
    2. Down -> Down -> Right -> Right

    --- Example 2 ---
    Input: obstacleGrid = [[0,1],[0,0]]
    Output: 1


    *** Constraints ***
    m == obstacleGrid.length
    n == obstacleGrid[i].length
    1 <= m, n <= 100
    obstacleGrid[i][j] is 0 or 1.

*/

#include <cstring>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  93.05% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(ROWS * COLS) */
class Solution_Top_Down__Memoization {
private:
    int memo[101][101];

public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid)
    {
        const int ROWS = obstacleGrid.size();
        const int COLS = obstacleGrid[0].size();

        if (obstacleGrid[0][0] == 1)
            return 0;

        /* Memset */
        memset(memo, 0xff, sizeof(memo));

        return solve(ROWS-1, COLS-1, obstacleGrid);
    }

private:
    int solve(int row, int col, vector<vector<int>>& obstacleGrid)
    {
        const int ROWS = obstacleGrid.size();
        const int COLS = obstacleGrid[0].size();

        if (row < 0 || col < 0 || obstacleGrid[row][col] == 1)
            return 0;

        if (row == 0 && col == 0)
            return 1;

        if (memo[row][col] != -1)
            return memo[row][col];

        int up   = solve(row-1, col  , obstacleGrid);
        int left = solve(row  , col-1, obstacleGrid);

        return memo[row][col] = up + left;
    }
};
