#include <iostream>

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

/* Time  Beats: 53.77% */
/* Space Beats: 67.60% */

/* Time  Complexity: O(m * n) */
/* Space Complexity: O(m * n) */
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& grid)
    {
        int m = grid.size();
        int n = grid[0].size();

        if (grid[0][0] == 1 || grid[m-1][n-1] == 1)
            return 0;

        if (m == 1 && n == 1)
            return 1;

        vector<vector<long long>> dp(m, vector<long long>(n, 0));

        for (int i = m-1;i >= 0; i--)
        {
            for (int j = n-1;j >= 0; j--)
            {
                if ((i == m-1 && j == n-1) || grid[i][j] == 1 )
                {
                    dp[i][j] = 0;
                }
                else if(i == m-1 && j+1 < n-1 && dp[i][j+1] == 0)
                {
                    dp[i][j]=0;
                }
                else if (j == n-1 && i+1 < m-1 && dp[i+1][j] == 0 )
                {
                    dp[i][j]=0;
                }
                else if(i == m-1 || j == n-1)
                {
                    dp[i][j]=1;
                }
                else
                {
                    dp[i][j]=dp[i+1][j] + dp[i][j+1];
                }
            }
        }

        return dp[0][0];
    }
};





