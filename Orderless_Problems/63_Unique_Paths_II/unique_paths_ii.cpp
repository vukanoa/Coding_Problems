#include <iostream>
#include <vector>

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

	==========================================================================
	FUNCTION: int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid);
	==========================================================================

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

/* Time  Beats: 33.01%% */
/* Space Beats:  8.02% */

/* Time  Complexity: O(n^2) */
/* Space Complexity: O(n^2) */
class Solution_Naive{
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid)
    {
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();

        if (obstacleGrid[0][0] == 1)
            return 0;
        
        if (m == 1 && n == 1)
            return !obstacleGrid[0][0];
        
        if (m > 1 && n > 1 && obstacleGrid[0][1] == 1 && obstacleGrid[1][0] == 1)
            return 0;


        std::vector<std::vector<int>> dp(m, std::vector<int>(n, 0));

        for (int i = 1; i < m; i++)
        {
            dp[i][0] = 1;
            if (obstacleGrid[i][0] == 1)
            {
                dp[i][0] = 0;
                break;
            }
        }

        for (int j = 1; j < n; j++)
        {
            dp[0][j] = 1;
            if (obstacleGrid[0][j] == 1)
            {
                dp[0][j] = 0;
                break;
            }
        }

        for (int i = 1; i < m; i++)
        {
            for (int j = 1; j < n; j++)
            {
                if (obstacleGrid[i][j] == 1)
                    continue;

                dp[i][j] = dp[i][j - 1] + dp[i - 1][j];
            }
        }

        return dp[m - 1][n - 1];
    }
};




/* Time  Beats:   100% */
/* Space Beats: 80.46% */

/* Time  Complexity: O(n^2) */
/* Space Complexity: O(n) */
class Solution{
public:
	int uniquePathsWithObstacles(std::vector<std::vector<int>>& obstacleGrid)
	{
		int row = obstacleGrid.size();
		int col = obstacleGrid[0].size();

		std::vector<int> dp(col, 0);
		dp[0] = 1;

		for(int i = 0; i < row; i++)
		{
			for(int j = 0; j < col; j++)
			{
				if(obstacleGrid[i][j])
					dp[j] = 0;
				else if(j > 0)
					dp[j] += dp[j-1];
			}
		}

		return dp[col-1];
	}
};
