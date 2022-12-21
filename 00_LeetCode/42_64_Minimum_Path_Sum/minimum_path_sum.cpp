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

	put dp[i][j] = grid[i][j];

	If there is a row above the current row and if there is a column before
	the current column, we add dp[i][j] with the smaller value of those two.

	If either is absent, add only the present one.
	That is:
		if we are at the row    0, add only from current point's left
		if we are at the column 0, add only from current point's up

	If both are absent(though that happens only for the very first element)
	don't add anything on top of grid[i][j] value;

	After we've filled the entire "dp" matrix, just return dp[m - 1][n - 1]

*/


/* Time  Complexity: O(m * n) */
/* Space Complexity: O(m * n) */
class Solution {
public:
    int minPathSum(std::vector<std::vector<int>>& grid)
    {
        int m = grid.size();
        int n = grid[0].size();

        std::vector<std::vector<int>> dp(m, std::vector<int>(n, 0));

        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                dp[i][j] = grid[i][j];

                if (i > 0 && j > 0)
                    dp[i][j] += std::min(dp[i - 1][j], dp[i][j - 1]);
                else if (i > 0 && j == 0)
                    dp[i][j] += dp[i - 1][j];
                else if (i == 0 && j > 0)
                    dp[i][j] += dp[i][j - 1];
            }
        }

        return dp[m - 1][n - 1];
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
	Solution sol;

	/* Example 1 */
	std::vector<std::vector<int>> grid = {{1, 3, 1}, {1, 5, 1}, {4, 2, 1}};

	/* Example 2 */
	// std::vector<std::vector<int>> grid = {{1, 2, 3}, {4, 5, 6}};

	/* Example 3 */
	// std::vector<std::vector<int>> grid = {{1, 4, 8}, {3, 9, 2}, {3, 1, 3}};

	std::cout << "\n\t========================";
	std::cout << "\n\t=== MINIMUM PATH SUM ===";
	std::cout << "\n\t========================\n\n";

	print_matrix(grid);

	/* Solution */
	int result = sol.minPathSum(grid);

	std::cout << "\n\tMinimum Path Sum: " << result << "\n\n";

	return 0;
}
