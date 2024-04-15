#include <iostream>
#include <vector>


/*
	==============
	=== MEDIUM ===
	==============

	===========================
	63) Minimum Path Sum
	===========================

	============
	Description:
	============

	Given a "m x n" grid filled with non-negative numbers, find a path from top
	left to bottom right, which minimizes the sum of all numbers along its path

	=====
	Node: You can only move either down or right at any point in time.
	=====

	====================================================
	FUNCTION: int minPathSum(vector<vector<int>>& grid);
	====================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  grid = [[1, 3, 1], [1, 5, 1], [4, 2, 1]]
	Output: 7

	--- Example 2 ---
	Input:  grid = [[1, 2, 3], [4, 5, 6]]
	Output: 12

	*** Constraints ***
	m == grid.length
	n == grid[i].length
	1 <= m, n <= 200
	0 <= grid[i][j] <= 100

*/


/*
	------------
	--- IDEA ---
	------------

	We make an additional matrix named "dp"(Dynamic Programming).

	We iterate through entire matrix "grid" and at each point, that is:
	    'i' and 'j'
	
	Calculate Minimum Path Sums for the very first(0-th) row.
	Calculate Minimum path Sums for the very first(0-th) column.

	Start iterating from i = 1 and j = 1 since both 0-th row and 0-th column
	are calculated.
	
	At dp[i][j] put grid[i][j](which is the current value) + minimum out of
	either the cell above the current one, or the cell to the left of the
	current one.

	After we've filled the entire "dp" matrix, just return dp[m - 1][n - 1]

*/

/* Time  Beats: 98.17% */
/* Space Beats: 26.16% */

/* Time  Complexity: O(m * n) */
/* Space Complexity: O(m * n) */
class Solution {
public:
    int minPathSum(std::vector<std::vector<int>>& grid)
    {
        int m = grid.size();
        int n = grid[0].size();

        std::vector<std::vector<int>> dp(m, std::vector(n, 0));
        dp[0][0] = grid[0][0];

        for (int i = 1; i < m; i++)
            dp[i][0] = grid[i][0] + dp[i - 1][0];

        for (int j = 1; j < n; j++)
            dp[0][j] = grid[0][j] + dp[0][j - 1];

        for (int i = 1; i < m; i++)
        {
            for (int j = 1; j < n; j++)
                dp[i][j] += grid[i][j] + std::min(dp[i - 1][j], dp[i][j - 1]);
        }

        return dp[m - 1][n - 1];
    }
};




/*
	------------
	--- IDEA ---
	------------

	Upon further looking at the problem or the previous Solution, we can notice
	that at each iteration of 'i' we only need one row. Though it is a bit
	different than that.

	Again:
	Calculate Minimum Path Sums for the very first(0-th) row.
	Calculate Minimum path Sums for the very first(0-th) column.

	Also, again start iterating from i = 1, j = 1.
	However we need the row[0] to be the corresponding dp[i][0] which is col[i]
	So at each iteration of 'i' we're putting col[i] into the row[0].

	This way we're ensuring that our row[j - 1] is always working whichever row
	we're on.

	At the end, just return row[n - 1].
*/

/* Time  Beats:  100% */
/* Space Beats: 75.73% */

/* Time  Complexity: O(m * n) */
/* Space Complexity: O(max(m, n)) */
class Solution_Optimized {
public:
    int minPathSum(std::vector<std::vector<int>>& grid)
    {
        int m = grid.size();
        int n = grid[0].size();

        std::vector<int> row(n, 0);
        row[0] = grid[0][0];
        for (int j = 1; j < n; j++)
            row[j] = row[j-1] + grid[0][j];
        
        std::vector<int> col(m, 0);
        col[0] = grid[0][0];
        for (int i = 1; i < m; i++)
            col[i] = col[i-1] + grid[i][0];

        for (int i = 1; i < m; i++)
        {
            row[0] = col[i];

            for (int j = 1; j < n; j++)
                row[j] = grid[i][j] + std::min(row[j-1], row[j]); // min(left, up)
        }

        return row[n-1];
    }
};



void
print_matrix(std::vector<std::vector<int>>& matrix)
{
	printf("\tMatrix:\n\t\t");
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix[0].size(); j++)
			printf("%2d ", matrix[i][j]);

		printf("\n\t\t");
	}
	printf("\n");
}


int
main()
{
	Solution           sol;
	Solution_Optimized sol_opt;

	/* Example 1 */
	std::vector<std::vector<int>> grid = {{1, 3, 1}, {1, 5, 1}, {4, 2, 1}};

	/* Example 2 */
	// std::vector<std::vector<int>> grid = {{1, 2, 3}, {4, 5, 6}};

	/* Example 3 */
	// std::vector<std::vector<int>> grid = {{1, 4, 8}, {3, 9, 2}, {3, 1, 3}};

	std::cout << "\n\t========================";
	std::cout << "\n\t=== MINIMUM PATH SUM ===";
	std::cout << "\n\t========================\n\n";


	/* Write Input */
	print_matrix(grid);


	/* Solution */
	// int result = sol.minPathSum(grid);
	int result = sol_opt.minPathSum(grid);


	/* Write Output */
	std::cout << "\n\tMinimum Path Sum: " << result << "\n\n";


	return 0;
}
